// Polymorphism — one interface, many behaviors; virtual dispatch picks at runtime.
// Why it matters: kills long if/else and switch chains; new types just plug in.
// CV hook: order types (LIMIT/MARKET) each execute() differently behind one call.
#include <bits/stdc++.h>
using namespace std;

struct Order { virtual void execute() const = 0; virtual ~Order()=default; };
struct LimitOrder  : Order { void execute() const override { cout << "match at limit price\n"; } };
struct MarketOrder : Order { void execute() const override { cout << "fill at best price\n";  } };

int main(){
    vector<Order*> book = { new LimitOrder(), new MarketOrder() };
    for (auto o : book) o->execute();       // same call, different behavior (no if/else on type)
}
