# models.py

from sqlalchemy import Column, Integer, String, LargeBinary, ForeignKey
from app.database import Base

class Users(Base):
    __tablename__ = 'Users'

    id = Column(String, primary_key=True)
    name = Column(String)
    password = Column(String)

class Friends(Base):
    __tablename__ = 'Friends'

    index = Column(Integer, primary_key=True)
    user_id1 = Column(String, ForeignKey("Users.id"))
    user_id2 = Column(String, ForeignKey("Users.id"))

class Chats(Base):
    __tablename__ = 'Chats'

    chat_id = Column(Integer, primary_key=True)
    
    sender = Column(String)
    participant = Column(String)

    time = Column(String)

    type = Column(String)
    message = Column(String)
    media = Column(LargeBinary)
    
