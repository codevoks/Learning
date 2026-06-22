# Diagrams (Excalidraw)

Yahan apne **redraw challenges** aur architecture sketches save karo.

## Naya diagram kaise banaye

1. `Cmd + P` → type **`Excalidraw: Create new drawing`**
2. File yahan save karo (e.g. `00a-docker-stack.excalidraw.md`)
3. Module ke `NOTES.md` → `## My diagrams` mein link daalo:
   ```markdown
   - [[00a-docker-stack.excalidraw|Docker stack redraw]]
   ```

## Module-wise suggested filenames

| Module | Suggested drawing |
|--------|-------------------|
| 00a | `00a-docker-stack` |
| 00b | `00b-sync-vs-async` |
| 00c | `00c-fastapi-request-flow` |
| 00d | `00d-training-vs-inference` |
| 01 | `01-llm-token-stream` |
| 02 | `02-gateway-infra-layers` |
| 03 | `03-llm-gateway-full` |
| 05 | `05-rag-pipeline` |
| 07 | `07-langgraph-states` |
| 11 | `11-agentic-workflow` |

## Agar plugin load nahi hua

1. Obsidian **restart** karo (Cmd+Q → dubara kholo)
2. Settings → **Community plugins** → Restricted mode **OFF**
3. Excalidraw **Enabled** hona chahiye
4. `Cmd + P` → "Excalidraw" — commands dikhni chahiye

Installed version: **2.24.2** (manual install in `.obsidian/plugins/`)
