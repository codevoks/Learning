// Strategy — interchangeable algorithms behind one interface; pick at runtime.
// vs State: SAME UML, but Strategy = choose an algorithm; State = behavior changes with
// internal state (+ transitions). CV hook: pluggable payment / split / fallback strategy.
#include <bits/stdc++.h>
using namespace std;

struct PaymentStrategy { virtual void pay(double a) const = 0; virtual ~PaymentStrategy()=default; };
struct UpiPayment  : PaymentStrategy { void pay(double a) const override { cout<<"UPI "<<a<<"\n"; } };
struct CardPayment : PaymentStrategy { void pay(double a) const override { cout<<"Card "<<a<<"\n"; } };

class Checkout {
    PaymentStrategy* strategy;                       // injected, swappable
public:
    explicit Checkout(PaymentStrategy* s): strategy(s) {}
    void setStrategy(PaymentStrategy* s){ strategy=s; }
    void pay(double a){ strategy->pay(a); }
};
int main(){
    UpiPayment upi; CardPayment card;
    Checkout c(&upi); c.pay(100);                    // UPI 100
    c.setStrategy(&card); c.pay(200);                // Card 200  (new strategy, no Checkout change)
}
