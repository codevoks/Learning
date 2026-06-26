// Why a polymorphic base needs a VIRTUAL destructor.
#include <bits/stdc++.h>
using namespace std;
struct BadBase  { ~BadBase()  { cout<<"~BadBase\n"; } virtual void f(){} };   // non-virtual dtor
struct BadDer   : BadBase { string* p=new string("leak"); ~BadDer(){ delete p; cout<<"~BadDer\n"; } };
struct GoodBase { virtual ~GoodBase(){ cout<<"~GoodBase\n"; } virtual void f(){} };
struct GoodDer  : GoodBase { string* p=new string("ok"); ~GoodDer(){ delete p; cout<<"~GoodDer\n"; } };
int main(){
    cout<<"-- non-virtual base dtor (BUG: ~BadDer skipped, p leaks) --\n";
    BadBase* b = new BadDer(); delete b;            // only ~BadBase runs -> leak (UB)
    cout<<"-- virtual base dtor (correct) --\n";
    GoodBase* g = new GoodDer(); delete g;          // ~GoodDer then ~GoodBase
}
// LESSON: delete via base pointer needs virtual ~Base() or derived dtor is skipped.
