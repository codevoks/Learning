"""A3 — Load .env and print masked DATABASE_URL. Complete the TODOs."""

# TODO: import load_dotenv and os
from dotenv import load_dotenv
import os

# TODO: call load_dotenv()
load_dotenv()

def mask_url(url: str | None) -> str:
    """Hide password in connection string. Example: devpass → dev***"""
    # TODO: implement — if no URL, return "missing"
    if url is None:
        return "missing"
    index = url.find('@')
    index1 = url.find(':')
    index2 = url.find(':', index1+1)
    password=url[index2+1:index]
    length=len(password)
    mask="*"*length
    newUrl = url[:index2]+mask+url[index:]
    return newUrl
    raise NotImplementedError


if __name__ == "__main__":
    # TODO: get DATABASE_URL from env, print mask_url(result)
    value = os.getenv("DATABASE_URL")
    print(mask_url(value));
    pass
