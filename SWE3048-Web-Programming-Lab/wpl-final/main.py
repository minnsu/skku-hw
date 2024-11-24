# main.py
from app.database import *
from app.schemas import *
from app.models import *

from fastapi import FastAPI, Depends, HTTPException, Request, WebSocket, WebSocketDisconnect
from fastapi.templating import Jinja2Templates
from fastapi.responses import Response, HTMLResponse, FileResponse, RedirectResponse
from fastapi.staticfiles import StaticFiles
from sqlalchemy.orm import Session
from pydantic import BaseModel
from typing import Annotated

from fastapi_login import LoginManager
from fastapi_login.exceptions import InvalidCredentialsException

from sqlalchemy import select, and_, or_, not_
from typing import List

import json
import base64

Base.metadata.create_all(bind=engine)
app = FastAPI()
def get_db():
    db = SessionLocal()
    try:
        yield db
    finally:
        db.close()

app.mount("/static", StaticFiles(directory="static", html=True), name="static")
templates = Jinja2Templates(directory="templates")

open_chats = dict()
""" open_chats의 구조: participant를 key로 하는 dictionary가 존재하며, 이 내부 dictionary는 각 user id를 key로 웹소켓 객체를 저장한다.
-> 브로드캐스트할 때 participant에 따라 데이터 송신 가능
{
    "user0,user1,user2": {
        "user0": websocket_object, "user1": websocket_object, "user2": websocket_object
    }
}
"""

# web socket
class ConnectionManager:
    def __init__(self):
        self.active_connections = []
    
    async def connect(self, websocket):
        await websocket.accept()
        self.active_connections.append(websocket)
    
    async def disconnect(self, websocket):
        self.active_connections.remove(websocket)
    
    async def broadcast(self, chat : dict, participant: str):
        for user, connection in open_chats[participant].items(): # participant에 접속해있는 웹소켓 객체에 데이터를 보낸다.
            await connection.send_text(json.dumps(chat))

manager = ConnectionManager()

class NotAuthenticationException(Exception):
    pass

SECRET = "super=secret-key"
login_manager = LoginManager(SECRET, '/token', use_cookie=True,
                             custom_exception=NotAuthenticationException)

@login_manager.user_loader
def get_user(id: str):
    db = SessionLocal()
    return db.query(Users).filter(Users.id==id).first()

@app.exception_handler(NotAuthenticationException)
def auth_exception_handler(request: Request, exc: NotAuthenticationException):
    return RedirectResponse(url="/")

@app.post("/token")
def post_login(user: User, db: Session=Depends(get_db)):
    # Users에서 입력으로 들어온 데이터에 따라 id, password를 검사 후 정상이면 response를, 비정상이면 Exception을 발생
    response = Response()
    db_user = db.query(Users).filter(and_(Users.id==user.id, Users.password==user.password)).first()
    if db_user and db_user.password == user.password:
        # access token  생성 후 response에 저장
        access_token = login_manager.create_access_token(
            data={'sub': user.id}
        )
        login_manager.set_cookie(response, access_token)
        return response
    else:
        raise HTTPException(status_code=422)

@app.websocket("/ws")
async def websocket_endpoint(websocket: WebSocket):
    await manager.connect(websocket)
    try:
        user = ''
        participant = ''
        while True:
            data = await websocket.receive_text()
            data = json.loads(data)
            if 'connect' in data:
                # 유저 첫 연결이면 웹소켓 객체 저장
                user = data['connect']
                participant = ','.join(data['participant'])
                
                if participant not in open_chats:
                    open_chats[participant] = dict()
                open_chats[participant][user] = websocket
            else:
                new_chat = None
                # 데이터에 따라 다르게 저장
                if 'message' in data:
                    new_chat = Chats(sender=user, participant=participant, time=data['time'], message=data['message'], type=data['type'])
                elif 'media' in data:
                    media = base64.b64decode(data['media'])
                    new_chat = Chats(sender=user, participant=participant, time=data['time'], media=media, type=data['type'])
                db = SessionLocal()
                db.add(new_chat)
                db.commit()
                db.refresh(new_chat)

                await manager.broadcast(data, participant)
    except WebSocketDisconnect:
        del open_chats[participant][user]
    except Exception as e:
        pass
    finally:
        await manager.disconnect(websocket)



@app.get("/")
def get_index(request : Request=None):
    return templates.TemplateResponse("index.html", {"request": request})

@app.get("/register")
def get_register(request: Request=None):
    # 회원가입 페이지
    return templates.TemplateResponse("register.html", {"request": request})

@app.post("/register")
def post_register(user: User, db: Session=Depends(get_db)):
    # 회원가입 데이터 처리
    response = dict()
    user_exist = db.query(Users).filter(Users.id==user.id).first() != None
    if user_exist:
        # 이미 존재하면 Fail 송신
        response['status'] = 'FAIL'
        response['error'] = 'EXIST_USER'
        response['text'] = 'User already exist in same id'
    else:
        # 없으면 생성 후 Success 송신
        new_user = Users(id=user.id, name=user.name, password=user.password)
        db.add(new_user)
        db.commit()
        db.refresh(new_user)

        response['status'] = 'SUCCESS'
        response['text'] = 'Successfully add user.'
    return response

@app.get("/main")
def get_main(request: Request=None, db: Session=Depends(get_db), user: User=Depends(login_manager)):
    # 메인 페이지: 친구 리스트, 채팅방 리스트
    return templates.TemplateResponse("/main.html", {"request": request, "user": user.id})

@app.post("/friends")
def post_friends(user: User=Depends(login_manager), db: Session=Depends(get_db)):
    # 친구 리스트 요청 처리
    friendship = db.query(Friends).filter(or_(Friends.user_id1==user.id, Friends.user_id2==user.id)).all()
    # 요청한 유저를 포함해서 친구들의 id와 name을 송신
    friends_name = [[user.id, user.name]]
    for friend in friendship:
        friend_user = db.query(Users).filter(or_(Users.id==friend.user_id1, Users.id==friend.user_id2)).all()
        for x in friend_user:
            if x.id != user.id:
                friends_name.append([x.id, x.name])
    return friends_name

@app.post("/chats")
def post_chats(user: User=Depends(login_manager), db: Session=Depends(get_db)):
    # 채팅방 리스트 요청: 유저 아이디가 participant에 포함된 채팅을 전부 반환 -> 프론트에서 마지막 채팅만 보이도록    
    datas = db.query(Chats).filter(Chats.participant.like(f"%{user.id}%")).all()
    for data in datas:
        if data.type != "text" and data.type != "INIT":
            data.media = base64.b64encode(data.media)
    return datas

@app.post("/id2name")
def post_id2name(participants: Participant, db: Session=Depends(get_db)):
    # id를 participant로 넘기면, name으로 바꾸어 보내준다. -> 프론트에서 id를 name으로 변환할 수 있도록 지원
    name_list = []
    for id in participants.id_list:
        target = db.query(Users).filter(Users.id==id).first()
        if target is not None:
            name_list.append(target.name)
    return name_list


@app.post("/add_friend")
def post_add_friend(friend: User, db: Session=Depends(get_db), user: User=Depends(login_manager)):
    # 친구 추가 처리

    if db.query(Users).filter(Users.id==friend.id).first() is None: # 요청한 아이디가 존재하지 않으면
        raise HTTPException(status_code=422)
    elif db.query(Friends).filter(or_(and_(Friends.user_id1==user.id, Friends.user_id2==friend.id), and_(Friends.user_id1==friend.id, Friends.user_id2==user.id))).first() is not None:
        # 이미 친구이면
        raise HTTPException(status_code=422)
    elif friend.id == user.id:
        # 요청한 아이디가 유저의 아이디면
        raise HTTPException(status_code=422)
    
    # 정상 추가 처리
    new_friend = Friends(user_id1=user.id, user_id2=friend.id)
    print(friend.id)
    db.add(new_friend)
    db.commit()
    db.refresh(new_friend)

    response = {"status": "SUCCESS"}
    return response


@app.post("/newchat")
def post_newchat(participants: Participant, request: Request=None, db: Session=Depends(get_db), user: User=Depends(login_manager)):
    # 새로운 채팅방 생성 처리
    print(participants.id_list)
    if db.query(Chats).filter(Chats.participant==','.join(participants.id_list)).first() is None:
        # 이미 동일한 유저들로 이루어진 채팅방이 없는 경우에만 생성
        init_message = Chats(sender=user.id, participant=','.join(participants.id_list), time='INIT', message="INIT", type="INIT")
        db.add(init_message)
        db.commit()
        db.refresh(init_message)
    # Success 송신
    return {"status": "SUCCESS", "participant": participants.id_list}

@app.get("/chat")
def get_chat(participant: str, request: Request=None, db: Session=Depends(get_db), user: User=Depends(login_manager)):
    # 채팅방으로 이동
    return templates.TemplateResponse("/chat.html", {"request": request, "participant": participant})


@app.post("/load_chats")
def post_load_chat(participant: Participant, user: User=Depends(login_manager), db: Session=Depends(get_db)):
    # 요청한 유저의 아이디와 함께, participant로 요청한 사용자로 구성된 채팅방의 채팅을 보냄 -> 채팅방 초기 채팅 전체 불러오기
    datas = db.query(Chats).filter(Chats.participant==','.join(participant.id_list)).all()
    for data in datas:
        if data.type != "text" and data.type != "INIT":
            data.media = base64.b64encode(data.media)
    return {"data": datas, "user": user.id}