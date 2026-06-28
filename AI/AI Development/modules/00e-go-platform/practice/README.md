# Practice — Module 00e Go Platform

> **Pehle padho**: `../MODULE.md` **§0 se §5 tak order mein** — revision sheet nahi, textbook hai.  
> Ek section → uska assignment → agla section.

## Setup

```bash
cd modules/00e-go-platform/practice
go mod tidy
go run .
```

## A3 — Python stub (doosri terminal)

00c practice ya koi FastAPI app port 8001 pe:

```bash
# example: 00c FastAPI on 8001 with POST /internal/query echo
```

Ya temporary:

```bash
python3 -c "
from http.server import BaseHTTPRequestHandler, HTTPServer
class H(BaseHTTPRequestHandler):
    def do_POST(self):
        print(self.headers.get('X-Tenant-ID'))
        self.send_response(200); self.end_headers(); self.wfile.write(b'ok')
HTTPServer(('',8001), H).serve_forever()
"
```

## Pass

- `curl localhost:8080/health` → `{"ok":true}`
- `curl -H "X-API-Key: test" -d '{}' localhost:8080/v1/query` → proxies with tenant header
