"""A1/A2/A4 — Chat echo with auth dependency."""

# TODO: import APIRouter, Depends
from fastapi import APIRouter, Depends
# TODO: import ChatMessage, ChatEcho from app.models
from app.models import ChatMessage, ChatEcho
# TODO: import verify_api_key from app.deps
from app.deps import verify_api_key

# router = None  # TODO: APIRouter(tags=["chat"], prefix="/chat" optional — pick one style)
router = APIRouter(tags=["chat"])

# TODO: POST "" or "/chat" — body ChatMessage, response_model ChatEcho
@router.post("/chat", response_model=ChatEcho)
async def chat(body: ChatMessage, api_key:str=Depends(verify_api_key)):
    return ChatEcho(reply=body.message.upper())
# TODO: Depends(verify_api_key) on route
# TODO: return ChatEcho(reply=body.message.upper()) or similar
