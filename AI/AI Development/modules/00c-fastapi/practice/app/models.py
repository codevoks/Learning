"""Pydantic request/response models for practice routes."""

from pydantic import BaseModel, Field

# TODO A1: ChatMessage body — message: str, Field(min_length=1)

class ChatMessage(BaseModel):
    message:str=Field(min_length=1)


# TODO A1: ChatEcho response — reply: str, echoed: bool = True


class ChatEcho(BaseModel):
    reply:str
    echoed:bool=True
