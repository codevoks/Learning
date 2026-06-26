// ISP — Interface Segregation: don't force clients to depend on methods they don't use.
// VIOLATION: one fat interface Worker { work(); eat(); } -> a Robot must implement eat() (meaningless).
// FIX: split into focused interfaces; a class implements only what applies.
#include <bits/stdc++.h>
using namespace std;

struct Workable { virtual void work() = 0; virtual ~Workable()=default; };
struct Eatable  { virtual void eat()  = 0; virtual ~Eatable()=default; };

struct Human : Workable, Eatable {            // needs both
    void work() override { cout << "human working\n"; }
    void eat()  override { cout << "human eating\n";  }
};
struct Robot : Workable {                      // only Workable — no pointless eat()
    void work() override { cout << "robot working\n"; }
};
int main(){ Human h; Robot r; h.work(); h.eat(); r.work(); }
