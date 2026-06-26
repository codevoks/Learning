"""A3 — Load .env and print masked DATABASE_URL. Complete the TODOs."""

# TODO: import load_dotenv and os

# TODO: call load_dotenv()

def mask_url(url: str | None) -> str:
    """Hide password in connection string. Example: devpass → dev***"""
    # TODO: implement — if no URL, return "missing"
    raise NotImplementedError


if __name__ == "__main__":
    # TODO: get DATABASE_URL from env, print mask_url(result)
    pass
