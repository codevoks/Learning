// overload (same scope, diff params) vs override (virtual, derived) vs hide (name hiding).
#include <bits/stdc++.h>
using namespace std;
struct Base {
    virtual void f(int){ cout<<"Base::f(int)\n"; }       // virtual -> overridable
    void g(int){ cout<<"Base::g(int)\n"; }
    void g(double){ cout<<"Base::g(double)\n"; }         // OVERLOAD (same scope)
};
struct Der : Base {
    void f(int) override { cout<<"Der::f(int) [override]\n"; }
    void g(int){ cout<<"Der::g(int) [hides Base::g]\n"; } // HIDES both Base::g overloads
};
int main(){
    Der d; Base* b=&d;
    b->f(10);          // Der::f  (override -> runtime)
    d.g(10);           // Der::g  (Base::g(double) hidden! use `using Base::g;` to keep it)
}
