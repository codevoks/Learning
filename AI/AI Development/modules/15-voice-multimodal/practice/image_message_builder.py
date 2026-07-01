"""A2 — Multimodal (vision) message payload banao.

`python image_message_builder.py` → `_check()` ke asserts pass. Harness edit mat karo.

Contract:
- build_image_message(text, image_url, detail="auto") -> dict:
  OpenAI-style user message jisme `content` ek LIST ho —
  ek {"type":"text","text":text} part aur ek
  {"type":"image_url","image_url":{"url":image_url,"detail":detail}} part.
  `detail` default "auto".
"""


def build_image_message(text: str, image_url: str, detail: str = "auto") -> dict:
    # TODO: {"role":"user","content":[ text_part, image_part ]}
    raise NotImplementedError


# ---------------------------------------------------------------------------
# PASS CRITERIA (edit mat karo)
# ---------------------------------------------------------------------------
def _check() -> None:
    msg = build_image_message("Is invoice ka total kya hai?", "https://x/inv.png", detail="high")
    assert msg["role"] == "user", "role user hona chahiye"
    assert isinstance(msg["content"], list) and len(msg["content"]) == 2, "content = 2-part list"

    text_parts = [p for p in msg["content"] if p.get("type") == "text"]
    img_parts = [p for p in msg["content"] if p.get("type") == "image_url"]
    assert len(text_parts) == 1 and len(img_parts) == 1, "ek text + ek image part"
    assert text_parts[0]["text"] == "Is invoice ka total kya hai?", "text content"
    assert img_parts[0]["image_url"]["url"] == "https://x/inv.png", "image url"
    assert img_parts[0]["image_url"]["detail"] == "high", "detail pass hona chahiye"

    default = build_image_message("hi", "u")
    di = [p for p in default["content"] if p.get("type") == "image_url"][0]
    assert di["image_url"]["detail"] == "auto", "default detail 'auto'"
    print("OK: image_message_builder A2 pass — multimodal message shape verified")


if __name__ == "__main__":
    _check()
