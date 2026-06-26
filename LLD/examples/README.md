# LLD Examples — C++ Reference Library 🔥

> **Study material** (complete, runnable). Yeh `problems/` se alag hai — problems tum solve karte ho (stubs); yeh **canonical reference** hai har OOP concept / SOLID principle / GoF pattern ka. Padho, run karo, redraw karo.
> Build any file: `g++ -std=c++17 file.cpp -o ex && ./ex`

## Visual learner tip
Har file ke top pe ek comment-block hai: **intent + when-to-use + when-NOT + real/CV hook + UML hint**. Pehle woh padho, phir code, phir bina dekhe class diagram redraw karo.

## OOP fundamentals (`oop/`)
4 pillars + composition-vs-inheritance.
| File | Concept |
|------|---------|
| `oop/encapsulation.cpp` | data hide + invariants (`private` + methods) |
| `oop/abstraction.cpp` | expose essential, hide detail (abstract base) |
| `oop/inheritance.cpp` | is-a reuse (`virtual`, base ctor) |
| `oop/polymorphism.cpp` | one interface, many behaviors (virtual dispatch) |
| `oop/composition_vs_inheritance.cpp` | favor composition (has-a) |

## SOLID (`solid/`) — each file: ❌ violation + ✅ fix
| File | Principle |
|------|-----------|
| `solid/srp.cpp` | Single Responsibility |
| `solid/ocp.cpp` | Open/Closed |
| `solid/lsp.cpp` | Liskov Substitution |
| `solid/isp.cpp` | Interface Segregation |
| `solid/dip.cpp` | Dependency Inversion |

## Design patterns (`patterns/`)
**Creational**: singleton, factory_method, abstract_factory, builder, prototype
**Structural**: adapter, decorator, facade, composite, proxy, bridge, flyweight
**Behavioral**: strategy, observer, state, command, template_method, iterator, chain_of_responsibility, mediator, memento, visitor

> All 23 GoF patterns covered. Confusing pairs to internalize: Strategy vs State, Decorator vs Proxy vs Adapter, Factory Method vs Abstract Factory. See `VISUAL-STUDY-GUIDE.md`.

## Also remember (principles, not patterns)
**DRY** (no duplication) · **KISS** (simplest that works) · **YAGNI** (build only what's needed) · favor **composition over inheritance** · program to **interfaces** · **dependency injection** (pass collaborators in; don't `new` inside).
