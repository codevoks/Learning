// State — an object's behavior changes with its internal state; states own transitions.
// vs Strategy: same structure, but here the object MOVES between states (a state machine).
// CV hook: refund / order state machine (PLACED -> SHIPPED -> DELIVERED).
#include <bits/stdc++.h>
using namespace std;
class Order;
struct State { virtual void next(Order& o) = 0; virtual string name() const = 0; virtual ~State()=default; };

class Order {
    State* state;
public:
    Order(State* s): state(s) {}
    void setState(State* s){ state=s; }
    void next(){ state->next(*this); }
    string status() const { return state->name(); }
};
struct Delivered : State { void next(Order&) override {} string name() const override { return "DELIVERED"; } };
struct Shipped   : State { void next(Order& o) override; string name() const override { return "SHIPPED"; } };
struct Placed    : State { void next(Order& o) override; string name() const override { return "PLACED"; } };
void Shipped::next(Order& o){ o.setState(new Delivered()); }
void Placed::next(Order& o){ o.setState(new Shipped()); }

int main(){
    Order o(new Placed());
    cout<<o.status()<<"\n"; o.next();                // PLACED -> SHIPPED
    cout<<o.status()<<"\n"; o.next();                // SHIPPED -> DELIVERED
    cout<<o.status()<<"\n";
}
