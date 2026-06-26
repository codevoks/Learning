# LLD Problems — C++ Practice 🔥

> Har problem ka apna folder: `README.md` (requirements + passing criteria) + `solution.cpp` (starter stub jise tum complete karoge). **Coach poora code nahi dega** — tum likhoge, review hoga.

## How to attack each problem
1. `README.md` padho → requirements clarify karo (coach se)
2. Entities + class diagram banao (NOTES / Excalidraw)
3. Patterns chuno + justify (kaunsa SOLID)
4. `solution.cpp` ke `// TODO` complete karo
5. Compile + run: `g++ -std=c++17 solution.cpp -o sol && ./sol` → asserts pass + prints `PASS`
6. Extensibility: "naya requirement aaye toh kitna change?" — defend

## Problem set
| # | Problem | Key patterns | Folder |
|---|---------|--------------|--------|
| 1 | Parking Lot | Strategy, Factory | `parking-lot/` |
| 2 | Elevator System | State, Strategy | `elevator-system/` |
| 3 | Vending Machine | State | `vending-machine/` |
| 4 | Splitwise | Strategy, graph | `splitwise/` |
| 5 | BookMyShow | concurrency/locking | `bookmyshow/` |
| 6 | Tic-Tac-Toe | Strategy (win-check) | `tic-tac-toe/` |
| 7 | Snake & Ladder | composition | `snake-and-ladder/` |
| 8 | Library Management | — | `library-management/` |
| 9 | ATM | State | `atm/` |
| 10 | Logging Framework | Chain of Responsibility | `logging-framework/` |
| 11 | Chess | polymorphism | `chess/` |
| 12 | Food Delivery | Strategy (assignment) | `food-delivery-system/` |
| 13 | Cab Booking (Uber/Ola) | Strategy (matching+pricing), State | `cab-booking/` |
| 14 | Hotel Booking | Strategy (pricing), concurrency | `hotel-booking/` |
| 15 | Stack Overflow | composition, voting | `stack-overflow/` |
| 16 | Online Shopping Cart (Amazon) | Strategy (discount/payment), State | `online-shopping-cart/` |

> Difficulty ramp: 3 Vending → 6 Tic-Tac-Toe → 1 Parking → 4 Splitwise → 9 ATM → 13 Cab → 5 BookMyShow → 11 Chess → 16 Shopping.

## Design principles to apply everywhere
OOP 4 pillars · **SOLID** · **DRY** (no duplication) · **KISS** (simplest that works) · **YAGNI** (build only what's needed) · favor **composition over inheritance** · program to **interfaces** · **dependency injection** (pass collaborators in, don't `new` inside).
