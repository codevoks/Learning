// Pure virtual -> abstract class. All-pure-virtual + virtual dtor = a C++ "interface".
#include <bits/stdc++.h>
using namespace std;
struct Logger {                    // interface
    virtual void log(const string&) = 0;
    virtual ~Logger() = default;
};
struct ConsoleLogger : Logger { void log(const string& m) override { cout<<"[console] "<<m<<"\n"; } };
// Logger l;  // ERROR: cannot instantiate abstract class
int main(){
    unique_ptr<Logger> l = make_unique<ConsoleLogger>();
    l->log("hello");
}
