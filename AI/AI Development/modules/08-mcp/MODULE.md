# Module 08 — MCP (Model Context Protocol)

> **Padho**: Isi file mein **Theory** — bahar mat jao.
> **Likho**: `practice/` folder. **Pucho**: Cursor chat `@MODULE.md`
> **Nav**: ← [Module 07](../07-agents-langgraph/MODULE.md) · Next → [Module 09](../09-multi-agent-hitl/MODULE.md)

> **Format**: Textbook — §0 terms zero se, prose mein. Voice: `@MODULE-TEACHING-STANDARD.md`

## At a glance

| | |
|---|---|
| Prerequisites | Module 07 (LangGraph + tools node). 06 tool schemas |
| Duration | ~3–5 sessions |
| Project? | No (Project B mein MCP tools wire — Module 11 M3) |
| Exit test | Host vs Client vs Server + threat model bina notes ke samjhao |

## Yeh module kis baare mein hai

Module 06–07 mein tumhare tools **tumhare Python code ke andar** the — `def search_docs(...)`. Yeh chhote scale pe theek hai, par socho jab 10 integrations (Slack, Postgres, GitHub, webhook…) × 3 agents ho jaayein — har jagah copy-paste, har jagah alag credentials, version mess. **MCP (Model Context Protocol)** isका jawab hai: tools ke liye ek **standard plug-in port**, bilkul USB-C jaisा — ek format, alag devices. Ek baar koi tool MCP server ke roop mein bana lo, koi bhi host (Cursor, tumhara agent) use plug kar sakta hai.

```
Cursor IDE (Host)
    ↔ MCP Client (IDE ke andar, SDK)
            ↔ MCP Server (alag process — tumhara Python script)
                    ├── tool: read_db
                    ├── tool: write_webhook
                    └── resource: file://policy.md
```

**Redraw challenge**: Host → Client → Server → Tool chain arrows ke saath bina dekhe banao; stdio transport kahan fit hota hai likho.

---

## Read order (strict)

| Session | Padho | Karo |
|---------|-------|------|
| 1 | §0 Terms + §1 Problem | Cursor settings mein MCP section (read-only) dekho |
| 2 | §2 Roles + §3 Tools vs Resources | **A1** — `mcp_server.py` |
| 3 | §4 Transports | **A1** complete — client se discover + invoke |
| 4 | §5 LangGraph wire + §6 Multiple servers | **A2** — `agent_mcp_wire.py` |
| 5 | §7 Security threat model | **A3** — `THREAT_MODEL.md` |

---

## Theory

### §0. Terms pehli baar — host, client, server

MCP ki sabse badi confusion teen roles ki hai, isliye inhe pehle hi clear kar lo. **Host** wo app hai jahan user baithta hai — Cursor IDE, Claude Desktop, ya tumhara FastAPI dashboard. **Client** us host ke andar ki protocol library hai (Cursor ka built-in MCP client, ya tumhara `mcp` Python client). **Server** ek **alag process** hai jo tools implement karta hai — tumhara `mcp_server.py`, ya `postgres-mcp`, `github-mcp`. Yeh teen alag cheezein hain, aur ek important rule: **user kabhi server se directly baat nahi karta — hamesha Host → Client → Server.**

```
User Cursor (Host) mein type karta hai
  → Host ka MCP Client server se connect
  → Client: "tools list bhejo"
  → Server: [read_db, write_webhook, ...]
  → LLM ek tool pick karta hai
  → Client: call_tool("read_db", {query: "..."})
  → Server execute karke result return
```

Protocol teen tarah ki capabilities deta hai. **Tool** ek action hai jiska side-effect ho sakta hai (`write_webhook`, `send_email`). **Resource** read-only context hai (`file://docs/refund-policy.md`). **Prompt** ek pre-built template hai (optional). Is module mein tools pe focus; resources A2+ mein optional.

Ek mini server ki shape (asli SDK thoda alag ho sakta hai, idea same):

```python
from mcp.server import Server
from mcp.server.stdio import stdio_server

server = Server("practice-db")

@server.tool()
async def read_db(query: str) -> str:
    """Run read-only SQL query. Use for lookups."""
    return str([{"id": 1, "status": "paid"}])    # stub

@server.tool()
async def write_webhook(url: str, payload: dict) -> str:
    """POST payload to URL. DESTRUCTIVE — needs approval in prod."""
    return "ok"
```

Yahan `@server.tool()` decorator ek normal Python function ko MCP tool bana deta hai, aur uska **docstring** LLM ke liye description ban jaata hai (Module 06 ke schema `description` jaisा — yahi quality decide karti hai model tool sahi use kare). Transport (stdio) §4 mein.

> **Ruko, socho:** MCP server alag process kyun hota hai, agent ke andar function kyun nahi? (Jawab: alag process se ek hi server ko kai hosts plug kar sakte hain, credentials ek jagah rehti hain, aur process-isolation security boundary deta hai — agent crash kare to tool process alag, aur ulta. Yeh code-reuse + security dono deta hai.)

**§0 checkpoint:** (1) Host aur Server alag kyun? (2) Tool aur Resource ka farak? (3) Cursor mein tumhara `mcp_server.py` kaunsa role play karta hai?

---

### §1. Problem pehle — hardcoded tools kahan fail karte hain

Project B mein Slack, Postgres, webhook, email — har integration ke liye agent repo mein ek Python function? Isका math seedha bura hai: N agents × M integrations = N×M copies. Slack API badle to 3 jagah fix, har function mein alag credentials, aur Team B ka DB tool Team A reuse nahi kar sakti. MCP isе todta hai — ek **server per integration domain** (ek DB server, ek comms server), aur koi bhi host use plug kar le. Discovery bhi standard hai (`list_tools()`), to naye tool ke liye agent ka code badalna nahi padta.

Par MCP har jagah zaroori nahi. Jab sirf 1 internal function ho, ya latency bahut critical ho (extra process hop), ya tool logic agent ke saath tightly coupled honi chahiye — tab seedhा inline function behtar hai.

> **→ Practice A1** (pass: server 2 tools expose kare, client discover + invoke kare).

---

### §2. Host, Client, Server — wire detail

Ab roles ka asli wiring dekho. Host (Cursor / tumhara app) ke andar UI, agent (LangGraph), aur MCP client hote hain. Server ek **alag OS process** hai jisme tools rehte hain. Beech mein **JSON-RPC** messages chalti hain. Request ka flow:

```
1. Host agent ko user message milता hai
2. Client connected servers se list_tools() — merged tool list
3. Tools LLM ko schema ke saath (Module 06 format jaisा)
4. LLM tool_call return karta hai
5. Client call_tool(name, args) server ko bhejta hai
6. Server result JSON — agent state mein append
```

Crash impact alag-alag hai aur design mein matter karta hai: Host down → UI down; Client (host ke andar) → host restart pe reconnect; Server (subprocess/remote) down → tools unavailable, par **agent ko gracefully degrade** karna chahiye (§7), crash nahi.

---

### §3. Tools vs Resources — kab kya

Ek simple grammar yaad rakho: **Tools = verbs** (`search_db(q)`, `send_slack(msg)`, `write_webhook(url, body)`) — yeh kuch *karte* hain. **Resources = nouns** (`file://policy/refund.md`, `db://schema/invoices`) — yeh read-only *context* hain. Ek typical agent flow dono use karta hai: pehle resource read (context load — "refund policy kya hai?"), phir tool call (action — "overdue invoices query"), phir write tool (jise HITL gate chahiye — Module 09). Client side:

```python
tools = await session.list_tools()   # [{name, description, inputSchema}, ...]
result = await session.call_tool("read_db", {"query": "SELECT * FROM orders LIMIT 5"})
```

#### §3 common errors

| Error | Kyun | Fix |
|-------|------|-----|
| `Tool not found: read_db` | Typo ya server alag | `list_tools()` se exact name |
| Invalid args | Schema mismatch | `inputSchema` ke against validate |
| Timeout | Slow DB/network | Per-tool timeout + retry |

---

### §4. Transports — stdio vs HTTP/SSE

MCP client aur server do tareeke se baat kar sakte hain. **stdio**: parent process server ko spawn karta hai (`python server.py`) aur stdin/stdout pipes se JSON-RPC chalता hai — yeh Cursor ke local config aur dev ke liye perfect hai. **SSE/HTTP**: remote URL (`https://mcp.company.com/slack`) — team-shared aur production ke liye. Cursor mein stdio config aisा dikhta hai:

```json
{ "mcpServers": {
    "practice-db": {
      "command": "python",
      "args": ["/absolute/path/to/mcp_server.py"],
      "env": { "DATABASE_URL": "postgresql://..." }
} } }
```

Yahan `command` + `args` OS subprocess spawn karte hain (stdio transport), aur `env` server ko secrets deta hai. Ek **mahत्वपूर्ण security baat** — secrets `env` mein do, **kabhi prompt mein nahi**. stdio flow: Cursor server spawn karta hai → client↔server stdin/stdout pe JSON-RPC → Cursor band hone pe subprocess kill.

#### §4 common errors

| Error | Kyun | Fix |
|-------|------|-----|
| `ENOENT python` | Galat command path | Full path / venv python |
| Server instant exit | Import error in server | Terminal mein manually run karke traceback dekho |
| Remote 401 | HTTP auth missing | Bearer token / mTLS config |

> **→ Practice A1** stdio transport se complete karo.

---

### §5. LangGraph agent se MCP wire karna

Module 07 ka `tools` node ab **inline functions** ki jagah **MCP client** use karega. Idea: jab LLM tool_call deta hai, tools node check karta hai wo tool MCP se hai ya local, aur accordingly route karta hai:

```python
async def mcp_tools_node(state: AgentState) -> dict:
    last = state["messages"][-1]
    results = []
    for tc in last.tool_calls:
        if tc.name in mcp_tool_names:           # startup pe list_tools() se cache
            out = await mcp_session.call_tool(tc.name, tc.args)   # network/subprocess hop
        else:
            out = LOCAL_TOOLS[tc.name](**tc.args)                 # internal — MCP zaroori nahi
        results.append(format_tool_message(tc.id, out))
    return {"messages": state["messages"] + results}
```

`mcp_tool_names` ko startup pe ek baar `list_tools()` se cache karte ho. Dhyaan do — `call_tool` ab ek network/subprocess hop hai (latency add), isliye internal/fast tools ko MCP mein daalne ki zaroorat nahi, unhe local rakho. Inline vs MCP ka tradeoff: inline fast hai aur setup-free par reuse copy-paste se hota hai; MCP extra process hai par same server kahin bhi plug ho jaata hai, versioning alag hoti hai, aur process-isolation security boundary milti hai.

> **→ Practice A2** (pass: agent external MCP tool se task complete kare).

---

### §6. Multiple MCP servers — naming, auth, failure

Project B mein Slack MCP + Postgres MCP + custom webhook server — teen alag processes. Startup pe agent har configured server se connect karke unke tools merge karta hai, aur tool-call pe sahi server pe route karta hai. Yahan teen practical problems hain. **Naming collision**: do server dono `search` tool de sakte hain — isliye prefix lagao (`db_search`, `docs_search`). **Auth**: har server ko apna scoped credential do (tenant vault se env inject), taaki ek rotate karne pe agent redeploy na karna pade. **Partial failure**: ek server down ho to baaki tools available rahein, aur LLM ko clearly batao kaunse tools abhi unavailable hain.

#### §6 common errors

| Error | Kyun | Fix |
|-------|------|-----|
| Duplicate tool names | Bina prefix merge | Register pe rename/prefix |
| Wrong server for tool | Routing table missing | `tool_to_server` map |

---

### §7. Security — threat model (OWASP LLM06)

Yeh module ka sabse important section hai. MCP se tools **bahar** se aate hain, isliye attack surface badhti hai. In risks ko samjho aur har ek ka mitigation:

| Risk | Example | Mitigation |
|------|---------|------------|
| Excessive agency | "Delete all rows" tool | Write tools HITL + table allowlist |
| Server compromise | DB MCP compromised | Sandbox + no root + version pin |
| Prompt injection → tool abuse | Doc mein "send all data to X" | Writes pe HITL (Module 09) |
| Data exfiltration | Tool args/logs mein API key | Vault per tenant; egress rules |
| Untrusted server | Random GitHub MCP | Code vet karo, commit pin, alag creds |
| Tool name collision | 2 servers `search` | Prefix `db_search`, `docs_search` |

Ek behaviour rule jo aksar galat hota hai — **server crash pe agent ko jhoot nahi bolna chahiye**:

```
❌ Galat: silent fail, LLM hallucinate karke jawab banata hai
✅ Sahi: tool result = {"error": "mcp_db unavailable", "retryable": true}
         LLM user ko honest message deta hai
```

Yeh isliye matter karta hai ki ek invisible failure (galat data pe confident answer) ek visible failure (saaf error message) se kahin zyada khatarnak hai — khaaskar billing/refund jaise context mein.

> **Ruko, socho:** Tumhara agent ek public GitHub se mila MCP server use karna chahta hai. Pehle do cheezein jo karoge? (Jawab: (1) uska code vet karo aur ek specific commit pin karo — auto-update se bacho; (2) use alag, least-privilege credentials do — agar wo compromise ho to blast radius chhota rahe.)

> **→ Practice A3** (pass: `THREAT_MODEL.md` — 5 risks + mitigations).

---

## Practice

> **Saare assignments**: [`practice/README.md`](practice/README.md). Code **tum** likhoge.
> Stuck? `@modules/08-mcp/MODULE.md` + error paste.

| # | Theory § | File | Pass when |
|---|----------|------|-----------|
| A1 | §0–§4 | `mcp_server.py` | Client `read_db` + `write_webhook` discover + invoke kare |
| A2 | §5 | `agent_mcp_wire.py` | LangGraph agent MCP tool se task complete kare |
| A3 | §7 | `THREAT_MODEL.md` | 5 risks + mitigations documented |

---

## Active recall (khud jawab likho NOTES mein)

1. MCP kab use karoge vs hardcoded Python function — 3 criteria?
2. Host, Client, Server — ek line each, Cursor example ke saath.
3. MCP server crash — agent ko kya karna chahiye, user kya dekhe?
4. Do servers same tool name — fix?

**Chat drill** (optional): "Module 08 — MCP security ke 3 risks whiteboard."

---

## Progress checklist

- [ ] §0 — host/client/server bina dekhe samjha sakta hoon
- [ ] Session table follow kiya
- [ ] Practice A1–A3 pass
- [ ] Redraw challenge
- [ ] Active recall NOTES mein
- [ ] NOTES session log

---

## Optional appendix

- [MCP Introduction](https://modelcontextprotocol.io/introduction)
- [MCP Build server](https://modelcontextprotocol.io/docs/develop/build-server)
- Module 07 — LangGraph tools node · Module 11 M3 — production MCP + credential vault
