// Chain of Responsibility — pass a request along a chain until a handler handles it.
// Decouples sender from receiver; each handler decides to handle or forward.
// CV hook: approval levels, logging by severity, provider fallback cascade.
#include <bits/stdc++.h>
using namespace std;

struct Handler {
    Handler* next=nullptr;
    Handler* setNext(Handler* n){ next=n; return n; }
    virtual void handle(int amount){ if(next) next->handle(amount); } // default: forward
    virtual ~Handler()=default;
};
struct TeamLead : Handler {
    void handle(int amount) override {
        if (amount<=1000) cout<<"TeamLead approved "<<amount<<"\n"; else Handler::handle(amount);
    }
};
struct Manager : Handler {
    void handle(int amount) override {
        if (amount<=10000) cout<<"Manager approved "<<amount<<"\n"; else Handler::handle(amount);
    }
};
struct Director : Handler {
    void handle(int amount) override { cout<<"Director approved "<<amount<<"\n"; }
};
int main(){
    TeamLead tl; Manager m; Director d;
    tl.setNext(&m)->setNext(&d);
    tl.handle(500); tl.handle(5000); tl.handle(50000); // routed to the right level
}
