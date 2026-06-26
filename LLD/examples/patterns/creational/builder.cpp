// Builder — construct a complex object step by step; avoids the telescoping-constructor mess
// (Pizza(size, cheese, olives, mushroom, ...)). Fluent, readable, optional fields.
#include <bits/stdc++.h>
using namespace std;

struct Pizza {
    string size; bool cheese=false, olives=false, mushroom=false;
    string describe() const {
        string s = size + " pizza";
        if (cheese) s+=" +cheese"; if (olives) s+=" +olives"; if (mushroom) s+=" +mushroom";
        return s;
    }
};
class PizzaBuilder {
    Pizza p;
public:
    explicit PizzaBuilder(string size){ p.size = move(size); }
    PizzaBuilder& addCheese(){ p.cheese=true; return *this; }   // chainable
    PizzaBuilder& addOlives(){ p.olives=true; return *this; }
    PizzaBuilder& addMushroom(){ p.mushroom=true; return *this; }
    Pizza build(){ return p; }
};
int main(){
    Pizza pz = PizzaBuilder("large").addCheese().addMushroom().build();
    cout << pz.describe() << "\n";                  // large pizza +cheese +mushroom
}
