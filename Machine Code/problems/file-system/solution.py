"""In-memory File System — machine-coding stub (target 60 min). Run: python solution.py"""


class Node:
    def __init__(self, is_file: bool = False):
        self.is_file = is_file
        self.children: dict[str, "Node"] = {}
        self.content = ""


class FileSystem:
    def __init__(self):
        self.root = Node()
    def _walk(self, path: str, create: bool = False) -> Node:
        # TODO: split path by "/", traverse (create dirs if create=True), return node
        raise NotImplementedError
    def mkdir(self, path: str) -> None:
        # TODO: create dirs along path
        raise NotImplementedError
    def add_content(self, path: str, content: str) -> None:
        # TODO: create file if missing, append content
        raise NotImplementedError
    def read(self, path: str) -> str:
        # TODO: return file content
        raise NotImplementedError
    def ls(self, path: str) -> list[str]:
        # TODO: if file -> [filename]; if dir -> sorted child names
        raise NotImplementedError


if __name__ == "__main__":
    fs = FileSystem()
    fs.mkdir("/a/b")
    fs.add_content("/a/b/f.txt", "hello")
    fs.add_content("/a/b/f.txt", " world")
    assert fs.read("/a/b/f.txt") == "hello world"
    assert fs.ls("/a/b") == ["f.txt"]
    assert fs.ls("/a") == ["b"]
    print("PASS")

# PASSING CRITERIA: nested mkdir, append semantics, ls sorted, read returns content.
