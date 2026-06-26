# Module 00 — Spring Boot Foundations (IoC/DI)

> **Agent**: `@Memory.md` + `@Prompt.md` + this + `@NOTES.md` · Next → [01 Controllers](../01-routing-handlers/MODULE.md)

## Visual map
```
@Service class OrderService { OrderService(PaymentClient p){...} }  // you: no `new`
Spring: scan @Service -> create bean -> ctor needs PaymentClient -> inject it
beans: @Component/@Service/@Repository/@Configuration+@Bean
scopes: singleton (default) | prototype | request
auto-config + starters = convention over config
```
```mermaid
flowchart LR
    Scan[component scan] --> Container[IoC container] --> Beans[create + wire beans] --> App
```
**Mental model**: Spring ka dil = **IoC container** — tum `new` nahi karte, container beans banata + inject karta (= tumhari LLD DI, par automatic). Annotations = config. Auto-config sensible defaults deta.

**Redraw**: scan → container → wire beans.

## Objectives
1. IoC + DI (container wires)
2. Beans + stereotypes + scopes
3. Constructor vs field injection
4. Auto-config; profiles

## Topics
- JVM/JDK; Maven/Gradle + starters
- `@Component`/`@Service`/`@Repository`/`@Configuration`/`@Bean`
- constructor injection (preferred); bean scopes; component scanning
- auto-configuration; `application.yml`; profiles; `@SpringBootApplication`

## Assignments
| # | Task | Passing criteria |
|---|------|------------------|
| A1 | Service bean injected via constructor | Wired by container, runs |
| A2 | 2 profiles + `@ConfigurationProperties` | Profile switches config |

## Active recall
1. IoC/DI — container kya karta?
2. constructor vs field injection — kyun ctor?
3. bean scopes?

## Checklist
- [ ] IoC from memory · [ ] A1,A2 · [ ] NOTES updated
