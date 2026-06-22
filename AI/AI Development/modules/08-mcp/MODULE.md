# Module 08 — MCP (Model Context Protocol)

> **Agent spawn**: `@Memory.md` + this file + `@modules/08-mcp/NOTES.md`  
> **Nav**: ← [Module 07](../07-agents-langgraph/MODULE.md) · Next → [Module 09](../09-multi-agent-hitl/MODULE.md)

## At a glance

| | |
|---|---|
| Prerequisites | Module 07 |
| Duration | ~3–5 sessions |
| Project? | No |
| Exit test | MCP vs inline tools + threat model bina notes ke |

## Visual map

> **Kaise padho**: Pehle diagram dekho → topics padho → session end pe "Redraw challenge" bina dekhe draw karo

```mermaid
flowchart LR
    Host["Host app\n(Cursor / agent)"] <-->|stdio/HTTP| Client["MCP Client"]
    Client <-->|MCP protocol| Server["MCP Server"]
    Server --> T1["Tool: search"]
    Server --> T2["Tool: read file"]
    Server --> T3["Tool: DB query"]
```

```
Host (Cursor IDE)
    ↔  MCP Client (in-process)
            ↔  MCP Server (separate process)
                    ├── tool: search
                    ├── tool: read_file
                    └── tool: run_query
```

### Mental model (1 line)

Host MCP Client se baat karta hai, Client Server se — tools process ke bahar, protocol se plug-in hote hain.

### Redraw challenge

Host ↔ Client ↔ MCP Server ↔ Tools chain bina dekhe draw karo.

## Read order

1. Objectives → 2. Learning hooks → 3. Topics → 4. Assignments → 5. Coach se active recall

**Prerequisites**: Module 07  
**Duration**: ~3–5 sessions

## Objectives

1. MCP architecture: hosts, clients, servers
2. Tools/resources expose karna standard protocol se
3. Zapier-style integrations ko MCP tools banao

## Learning hooks

| Concept | Parallel |
|---------|----------|
| MCP server | Microservice with OpenAPI |
| Tool listing | API discovery / swagger |
| Resource URIs | REST resource paths |
| Auth | JWT-scoped integrations |

## Topics

- MCP vs inline function definitions
- stdio vs SSE transport
- Building a minimal MCP server (Python)
- Connecting LangGraph / gateway to MCP tools
- Security: sandbox, allowlists

## Assignments

| # | Task | Passing criteria |
|---|------|------------------|
| A1 | MCP server: `read_db` + `write_webhook` stubs | Client discovers + invokes both |
| A2 | Wire MCP tool into agent from Module 07 | Agent uses external MCP tool |
| A3 | Threat model doc | 5 risks + mitigations |

## Active recall

1. MCP kab use karoge vs hardcoded Python functions?
2. MCP server crash — agent behavior kya honi chahiye?
3. Multiple MCP servers — tool name collision kaise handle?

## Progress checklist

- [ ] Objectives recall bina notes ke
- [ ] Assignments A1–A3 pass
- [ ] NOTES.md session log updated
