// Inheritance — "is-a" reuse. Use sparingly; prefer composition unless a true is-a.
// When: subtype genuinely IS the base and substitutes for it (see LSP).
// UML: Animal <|-- Dog, Cat
#include <bits/stdc++.h>
using namespace std;

class Animal {
protected:
    string name;
public:
    Animal(string n): name(move(n)) {}
    virtual string sound() const = 0;       // each subtype defines its own
    void describe() const { cout << name << " says " << sound() << "\n"; } // reused by all
    virtual ~Animal() = default;
};
class Dog : public Animal {
public:
    Dog(string n): Animal(move(n)) {}       // call base ctor
    string sound() const override { return "Woof"; }
};
class Cat : public Animal {
public:
    Cat(string n): Animal(move(n)) {}
    string sound() const override { return "Meow"; }
};
int main(){
    Dog d("Tommy"); Cat c("Kitty");
    d.describe(); c.describe();             // shared describe(), specialized sound()
}
