// Observer — one-to-many: subject notifies all subscribers on change (pub-sub).
// Push vs pull: push sends data in notify(); pull lets observers query the subject.
// CV hook: Redis pub-sub fan-out / multi-channel notifications.
#include <bits/stdc++.h>
using namespace std;

struct Observer { virtual void update(int price) = 0; virtual ~Observer()=default; };
class Stock {                                        // the subject
    vector<Observer*> subs; int price=0;
public:
    void subscribe(Observer* o){ subs.push_back(o); }
    void setPrice(int p){ price=p; for(auto o:subs) o->update(p); } // notify all
};
struct Trader : Observer {
    string name; explicit Trader(string n):name(move(n)){}
    void update(int price) override { cout<<name<<" sees price "<<price<<"\n"; }
};
int main(){
    Stock s; Trader a("A"), b("B");
    s.subscribe(&a); s.subscribe(&b);
    s.setPrice(101);                                 // both A and B notified
}
