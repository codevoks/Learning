// Favor composition (has-a) over inheritance (is-a) for flexible reuse.
#include <bits/stdc++.h>
using namespace std;
struct Engine { virtual int power() const = 0; virtual ~Engine()=default; };
struct Petrol : Engine { int power() const override { return 100; } };
struct Electric: Engine { int power() const override { return 150; } };
class Car {                         // Car HAS-A Engine (composition) -> swappable
    Engine* engine;
public:
    explicit Car(Engine* e): engine(e) {}
    void setEngine(Engine* e){ engine=e; }
    int power() const { return engine->power(); }
};
int main(){
    Petrol p; Electric e;
    Car car(&p); cout<<car.power()<<"\n";   // 100
    car.setEngine(&e); cout<<car.power()<<"\n"; // 150 (retrofit at runtime; inheritance can't)
}
