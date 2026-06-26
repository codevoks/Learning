// RAII: acquire in ctor, release in dtor -> exception-safe, no manual cleanup.
#include <bits/stdc++.h>
using namespace std;
class Guard {                      // models a locked resource
    string name;
public:
    explicit Guard(string n): name(move(n)) { cout<<"acquire "<<name<<"\n"; }
    ~Guard(){ cout<<"release "<<name<<"\n"; }   // runs even if an exception is thrown
};
void work(){
    Guard g("lock");               // acquired
    cout<<"working...\n";
    // even if this threw, ~Guard would still release the lock (stack unwinding)
}                                  // released here automatically
int main(){ work(); cout<<"done\n"; }
// std::lock_guard, std::unique_ptr, std::fstream are all RAII wrappers.
