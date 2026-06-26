// Prototype — create new objects by CLONING an existing one (a configured prototype),
// instead of building from scratch. Useful when construction is costly or config-heavy.
#include <bits/stdc++.h>
using namespace std;

struct Enemy {
    string type; int hp, dmg;
    Enemy(string t, int h, int d): type(move(t)), hp(h), dmg(d) {}
    virtual unique_ptr<Enemy> clone() const { return make_unique<Enemy>(*this); } // copy self
    virtual ~Enemy() = default;
};
int main(){
    Enemy orc("orc", 100, 15);                      // configured prototype
    auto a = orc.clone();                           // cheap copies, then tweak
    auto b = orc.clone(); b->hp = 120;
    cout << a->type << " hp=" << a->hp << " | " << b->type << " hp=" << b->hp << "\n";
}
