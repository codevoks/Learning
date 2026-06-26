// const member functions, const& params, mutable.
#include <bits/stdc++.h>
using namespace std;
class Account {
    double balance;
    mutable int reads = 0;          // mutable: changeable even in a const method
public:
    explicit Account(double b): balance(b) {}
    double get() const { ++reads; return balance; }   // const method (can use on const objects)
    void deposit(double d) { balance += d; }          // non-const (mutates)
    int reads_count() const { return reads; }
};
void print(const Account& a){ cout<<"bal="<<a.get()<<"\n"; } // const& -> can call only const fns
int main(){
    const Account ca(100);
    print(ca);                      // ok: get() is const
    // ca.deposit(10);              // ERROR: non-const fn on const object
    cout<<"reads="<<ca.reads_count()<<"\n"; // mutable allowed the increment
}
