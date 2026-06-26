// Object slicing: assigning a Derived to a Base BY VALUE drops the derived part.
#include <bits/stdc++.h>
using namespace std;
struct Base { virtual string who() const { return "Base"; } virtual ~Base()=default; };
struct Derived : Base { string who() const override { return "Derived"; } };
void byValue(Base b){ cout<<"byValue -> "<<b.who()<<"\n"; }   // SLICES
void byRef(const Base& b){ cout<<"byRef   -> "<<b.who()<<"\n"; } // keeps Derived
int main(){
    Derived d;
    Base sliced = d;            // slicing: only Base copied, vptr = Base's
    cout<<"sliced -> "<<sliced.who()<<"\n";   // Base  (polymorphism lost)
    byValue(d);                 // Base   (sliced)
    byRef(d);                   // Derived (correct)
}
// FIX: pass/handle polymorphic objects by reference or pointer, never by value.
