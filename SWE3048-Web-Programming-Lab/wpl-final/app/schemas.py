# schemas.py
from pydantic import BaseModel
from typing import Optional, List

class User(BaseModel):
    id: str
    name: str
    password: str

class Participant(BaseModel):
    id_list: List[str]

class ChatCreate(BaseModel):
    sender: str
    participants: List[int]
 
    time: str
    message: Optional[str] = None
    media: Optional[bytes] = None

class Chat(ChatCreate):
    chat_id: int

