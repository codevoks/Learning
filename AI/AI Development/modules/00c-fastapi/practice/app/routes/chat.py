"""A1/A2/A4 — Chat echo with auth dependency."""

# TODO: import APIRouter, Depends
# TODO: import ChatMessage, ChatEcho from app.models
# TODO: import verify_api_key from app.deps

router = None  # TODO: APIRouter(tags=["chat"], prefix="/chat" optional — pick one style)


# TODO: POST "" or "/chat" — body ChatMessage, response_model ChatEcho
# TODO: Depends(verify_api_key) on route
# TODO: return ChatEcho(reply=body.message.upper()) or similar
