// Shallow copy shares the pointer (double-free); deep copy duplicates the data.
#include <bits/stdc++.h>
using namespace std;
struct Deep {                       // correct: deep copy
    int* p;
    Deep(int v): p(new int(v)) {}
    Deep(const Deep& o): p(new int(*o.p)) {}   // copies the VALUE
    ~Deep(){ delete p; }
};
int main(){
    // Shallow (what the COMPILER default would do for a raw ptr): both share p -> double free.
    // We show only the SAFE deep version running:
    Deep a(42);
    Deep b = a;                     // deep: b.p is a new int
    *b.p = 99;
    cout<<"a="<<*a.p<<" b="<<*b.p<<"\n";   // a=42 b=99 (independent)
    cout<<"PASS (deep copy -> independent, no double free)\n";
}
// Shallow copy would make a.p==b.p -> editing one hits both -> ~ twice -> double free (UB).
