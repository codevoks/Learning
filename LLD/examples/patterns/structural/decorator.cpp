// Decorator — add behavior by WRAPPING, keeping the same interface; stackable at runtime.
// Beats subclass explosion (CheeseMushroomPizza...). vs Proxy: proxy controls access, not adds features.
// CV hook: add-on pricing (cheese, toppings) layered on a base beverage/order.
#include <bits/stdc++.h>
using namespace std;

struct Beverage { virtual double cost() const = 0; virtual string desc() const = 0; virtual ~Beverage()=default; };
struct Coffee : Beverage { double cost() const override { return 50; } string desc() const override { return "coffee"; } };

struct AddOn : Beverage {                            // base decorator wraps a Beverage
    Beverage* inner; explicit AddOn(Beverage* b): inner(b) {}
};
struct Milk : AddOn { using AddOn::AddOn;
    double cost() const override { return inner->cost()+10; } string desc() const override { return inner->desc()+"+milk"; } };
struct Sugar : AddOn { using AddOn::AddOn;
    double cost() const override { return inner->cost()+5; }  string desc() const override { return inner->desc()+"+sugar"; } };

int main(){
    Beverage* order = new Sugar(new Milk(new Coffee())); // stack decorators
    cout << order->desc() << " = " << order->cost() << "\n"; // coffee+milk+sugar = 65
}
