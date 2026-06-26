// Abstract Factory — create FAMILIES of related objects without naming concretes.
// e.g. a UI toolkit: one factory makes a matching Button+Checkbox per OS theme.
// vs Factory Method: that makes one product; this guarantees a consistent family.
#include <bits/stdc++.h>
using namespace std;

struct Button   { virtual string render() const = 0; virtual ~Button()=default; };
struct Checkbox { virtual string render() const = 0; virtual ~Checkbox()=default; };
struct DarkButton   : Button   { string render() const override { return "[dark button]"; } };
struct DarkCheckbox : Checkbox { string render() const override { return "[dark checkbox]"; } };
struct LightButton  : Button   { string render() const override { return "[light button]"; } };
struct LightCheckbox: Checkbox { string render() const override { return "[light checkbox]"; } };

struct GUIFactory {                                 // the abstract factory
    virtual unique_ptr<Button>   button()   const = 0;
    virtual unique_ptr<Checkbox> checkbox() const = 0;
    virtual ~GUIFactory()=default;
};
struct DarkFactory : GUIFactory {
    unique_ptr<Button>   button()   const override { return make_unique<DarkButton>(); }
    unique_ptr<Checkbox> checkbox() const override { return make_unique<DarkCheckbox>(); }
};
struct LightFactory : GUIFactory {
    unique_ptr<Button>   button()   const override { return make_unique<LightButton>(); }
    unique_ptr<Checkbox> checkbox() const override { return make_unique<LightCheckbox>(); }
};
void renderUI(const GUIFactory& f){ cout << f.button()->render() << " " << f.checkbox()->render() << "\n"; }
int main(){ renderUI(DarkFactory()); renderUI(LightFactory()); } // always a matching family
