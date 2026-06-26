# Module 00 — Network Foundations

> **Agent spawn**: `@Memory.md` + `@Prompt.md` + this file + `@NOTES.md`
> **Nav**: Next → [01 Physical & Data Link](../01-physical-datalink/MODULE.md)

## At a glance
| | |
|---|---|
| Prerequisites | None |
| Duration | ~1 session |
| Exit test | OSI 7 layers + encapsulation |

## Visual map
```
OSI (7)            TCP/IP (4)     PDU       Example
7 Application ┐
6 Presentation├─ Application     data      HTTP, DNS, TLS
5 Session     ┘
4 Transport      Transport       segment   TCP, UDP
3 Network        Internet        packet    IP, ICMP
2 Data Link   ┐  Network Access  frame     Ethernet, ARP
1 Physical    ┘                  bits      cables

Encapsulation: [Eth|IP|TCP|App data|Eth-tr]  each layer adds its header
```
**Mental model**: Layering = har layer apna kaam, neeche wali pe trust. Data neeche jaate waqt headers add hote (encapsulation), upar jaate waqt strip (decapsulation). Interview mein har cheez ko "yeh kaunsi layer" se map karo.

**Redraw challenge**: OSI 7 layers + encapsulation stack.

## Objectives
1. Why layering
2. OSI 7 layers + jobs + PDUs
3. TCP/IP 4-layer + mapping
4. Encapsulation/decapsulation

## Topics
- Why layered models; protocol vs service
- OSI 7 layers: each job + PDU + example protocol
- TCP/IP 4-layer; OSI↔TCP/IP mapping
- Encapsulation/decapsulation; headers per layer

## Assignments
| # | Task | Passing criteria |
|---|------|------------------|
| A1 | Map 8 protocols to OSI layers | All correct |
| A2 | Draw encapsulation for an HTTP request | Headers in right order |

## Active recall bank
1. OSI 7 layers + ek example each?
2. PDU at transport vs network vs link?
3. OSI vs TCP/IP — kaunsi layers merge?

## Progress checklist
- [ ] 7 layers + encapsulation from memory
- [ ] A1, A2 done
- [ ] NOTES.md updated
