# Atlas AI — architecture flows (diagram-first)

Pictures first, then the one or two sentences that make each picture defensible in an interview.
Source of truth for the diagrams: `docs/system-design-visuals.md`, `docs/architecture.md`, and the
README in the implementation repo — reproduced/adapted here for study, not copied verbatim in bulk.

## 1. System context and trust boundaries

```mermaid
flowchart LR
    Browser[Browser UI] --> Web[Next.js web app / BFF]
    Web --> API[FastAPI control plane]
    API --> Postgres[(PostgreSQL - sole authority)]
    API --> ObjectStore[(Local object-store adapter)]
    Worker[Ingestion worker] --> API
    Worker --> Postgres
    Worker --> ObjectStore

    API --> Retrieval[Retrieval services]
    Retrieval --> Postgres
    API --> AI[Deterministic local AI adapters]
    AI --> Postgres

    API --> Security[Guardrails and quota policy]
    API --> Telemetry[Local no-content telemetry]
```

**Say this cold:** "Next.js never touches Postgres or a provider directly — everything goes through
FastAPI, which is the only place authorization decisions happen. That's one transaction boundary
and one place a tenant filter can't be forgotten."

## 2. Ingestion state machine

```mermaid
stateDiagram-v2
    [*] --> PENDING
    PENDING --> CLAIMED: worker leases (FOR UPDATE SKIP LOCKED)
    CLAIMED --> VERIFYING
    VERIFYING --> PARSING
    PARSING --> NORMALIZING
    NORMALIZING --> CHUNKING
    CHUNKING --> EMBEDDING
    EMBEDDING --> PUBLISHING
    PUBLISHING --> SUCCEEDED
    VERIFYING --> FAILED
    PARSING --> FAILED
    CHUNKING --> FAILED
    EMBEDDING --> FAILED
    FAILED --> RETRY_WAIT: transient, bounded attempts
    RETRY_WAIT --> CLAIMED
    PENDING --> CANCEL_REQUESTED
    CLAIMED --> CANCEL_REQUESTED
    CANCEL_REQUESTED --> CANCELLED
```

**Say this cold:** "Nothing is searchable until PUBLISHING completes atomically — chunks and
embeddings for a document version become visible in the same transaction as the version flipping to
READY. That's what makes a worker crash mid-pipeline safe: a half-processed version is never
half-visible."

## 3. Golden RAG flow (search → grounded answer)

```mermaid
sequenceDiagram
    participant User
    participant API
    participant DB as PostgreSQL

    User->>API: Ask a question
    API->>API: Authorize (membership + document:read)
    API->>DB: Semantic branch (tenant + ready-version filters, exact cosine)
    API->>DB: Lexical branch (same filters, Postgres FTS)
    API->>API: Deterministic RRF fusion + dedup by (chunk_id, version_id)
    API->>API: Context builder (bounded evidence, label untrusted excerpts)
    API->>API: Generate (evidence-only, no tools/network)
    API->>API: Citation validator (span+quote vs frozen AnswerEvidence)
    API->>DB: Persist answer_run + answer_evidence + citations
    API-->>User: Answer + per-citation verified/rejected status
```

**Say this cold:** "Both retrieval branches run under the exact same authorization filters — there
is no fusion step that runs *outside* the access-control boundary. And citation checking happens
*after* generation, against a frozen evidence snapshot the model can't influence."

## 4. Security / trust boundary map

```mermaid
flowchart TB
    User[User input and browser state\nUNTRUSTED] --> Web[Web UI]
    Web -->|session only| API[API authorization boundary]
    API -->|server-derived tenant context| Domain[Domain use cases]
    Domain --> Postgres[(Authoritative tenant data)]
    Domain --> ObjectStore[(Tenant-prefixed blobs)]

    Uploaded[Uploaded files\nUNTRUSTED] --> Parser[Parser and normalizer]
    Retrieved[Retrieved text\nUNTRUSTED evidence] --> Generator[Grounded generator]
    Generator --> Validator[Citation and safety validator]

    Security[Guardrails] --> Domain
    Security --> Validator
```

**Say this cold:** "Everything crossing a trust boundary — uploaded files, retrieved text, tool
output — is treated as data, never as instructions. System/developer policy always outranks
content. That single sentence is the entire prompt-injection defense philosophy in this system."

## 5. Bounded research state machine

```mermaid
stateDiagram-v2
    [*] --> Planned
    Planned --> RetrievingEvidence
    RetrievingEvidence --> Checkpointed
    Checkpointed --> AwaitingApproval
    AwaitingApproval --> Synthesizing: approved (fresh, current version)
    AwaitingApproval --> Cancelled: denied
    Synthesizing --> Completed
    RetrievingEvidence --> Failed: safe failure
    Synthesizing --> Failed: safety or citation failure
```

**Say this cold:** "The run cannot reach Synthesizing without an explicit, *current* human approval
— a stale approval version fails as a conflict, not a silent pass. Tools are limited to Atlas
retrieval and a local policy catalog; nothing that touches the outside world."

## 6. Worker failure/recovery (lease model)

```mermaid
sequenceDiagram
    participant W1 as Worker A
    participant DB as PostgreSQL
    participant W2 as Worker B

    W1->>DB: Lease job (FOR UPDATE SKIP LOCKED, lease_expiry = now+N)
    W1->>DB: heartbeat (extends lease)
    Note over W1: Worker A crashes mid-EMBEDDING
    Note over DB: lease_expiry passes, no heartbeat
    W2->>DB: Poll claimable jobs (lease expired)
    W2->>DB: Lease job (new owner, expected version check)
    W2->>W2: Resume from durable job state, not from scratch memory
    W2->>DB: Publish atomically once complete
```

**Say this cold:** "A worker's authority to publish is checked against lease owner *and* expected
job version at publish time — a worker that thinks it still owns a job but has actually lost its
lease can't corrupt state. Recovery is just 'another worker claims the same durable row,' not a
special crash-recovery code path."

## 7. Database responsibilities (who owns what)

| Store | Owns | Never owns |
|---|---|---|
| PostgreSQL | tenants, memberships, jobs, chunks, embeddings (JSONB exact-cosine baseline), evaluations, research state, security events, audit | large blobs, correctness resting solely on ephemeral locks |
| Object storage (local FS adapter) | immutable raw + normalized derived blobs, tenant-prefixed keys | authorization decisions, mutable job state |
| Redis | not in the default local stack yet; if introduced: ephemeral coordination/cache/rate-limit only | ever being the system of record |

**Say this cold:** "There is exactly one authoritative store — Postgres — including the current
vector baseline. That's a deliberate simplification (D03/D09): one transaction boundary, one place
tenant filters live, lower operational burden, at the cost of exact-cosine instead of an ANN index."
