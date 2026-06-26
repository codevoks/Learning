// Composition over inheritance — "has-a" beats "is-a" for flexible reuse.
// Inheritance is rigid (fixed at compile time, tight coupling). Composition lets you
// swap the collaborator at runtime and avoids fragile deep hierarchies.
// UML: Car o-- Engine   (Car HAS-A Engine, swappable)
#include <bits/stdc++.h>
using namespace std;

struct Engine { virtual int power() const = 0; virtual ~Engine()=default; };
struct PetrolEngine : Engine { int power() const override { return 100; } };
struct ElectricEngine : Engine { int power() const override { return 150; } };

class Car {
    Engine* engine;                         // composition: Car HAS-A Engine (injected)
public:
    explicit Car(Engine* e): engine(e) {}
    void setEngine(Engine* e){ engine = e; } // swap at runtime — impossible with inheritance
    int power() const { return engine->power(); }
};
int main(){
    Car car(new PetrolEngine());
    cout << "power = " << car.power() << "\n";    // 100
    car.setEngine(new ElectricEngine());          // retrofit without changing Car's type
    cout << "power = " << car.power() << "\n";    // 150
}
