# Module 02 — Network Layer & IP

> **Agent spawn**: `@Memory.md` + `@Prompt.md` + this file + `@NOTES.md`
> **Nav**: ← [01 Physical & Data Link](../01-physical-datalink/MODULE.md) · Next → [03 Routing](../03-routing/MODULE.md)

## At a glance
| | |
|---|---|
| Prerequisites | 01 |
| Duration | ~1–2 sessions |
| Exit test | Subnet a /24 + NAT flow + public vs private |

## Visual map
```
CIDR 192.168.1.0/26:
  /26 → 26 network bits, 6 host bits → 2^6 = 64 addrs, 62 usable
  network: .0   broadcast: .63   hosts: .1–.62
  next subnet: .64/26 ...

NAT: [private 10.0.0.5:5000] --router--> [public 1.2.3.4:40001] → internet
```
```mermaid
flowchart LR
    Priv[Private host 10.x] --> NAT[Router/NAT table]
    NAT --> Pub[Public IP:port] --> Net[Internet]
```
**Mental model**: IP = global logical addressing + routing. Subnetting = ek bada block ko chhote networks mein todna (host bits borrow karke). NAT = ek public IP ke peeche kai private hosts (IPv4 shortage ka jugaad).

**Redraw challenge**: Subnet /24→/26 split + NAT translation.

## Objectives
1. IPv4 header; IPv4 vs IPv6
2. Subnetting + CIDR math
3. NAT, DHCP, private IPs
4. ICMP, MTU/fragmentation

## Topics
- IPv4 header fields; IPv4 vs IPv6 (why v6)
- Classful vs classless; CIDR; subnetting (network/broadcast/host/usable)
- Private IP ranges; NAT (PAT); DHCP
- ICMP (ping, traceroute); MTU + fragmentation; default gateway

## Assignments
| # | Task | Passing criteria |
|---|------|------------------|
| A1 | 5 subnetting drills (CIDR → network, broadcast, range, #hosts) | All correct |
| A2 | Explain a real traceroute output | Each hop + TTL explained |

## Active recall bank
1. /26 mein kitne usable hosts?
2. NAT kya problem solve karta?
3. Private IP ranges kaunse?
4. ICMP ka kaam (ping/traceroute)?

## Progress checklist
- [ ] Subnetting + NAT from memory
- [ ] A1, A2 done
- [ ] NOTES.md updated
