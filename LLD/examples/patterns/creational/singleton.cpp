// Singleton — exactly one instance, global access point. Often an anti-pattern
// (hidden global state, hard to test) — prefer dependency injection. Know it for interviews.
// Thread-safe in C++11+: function-local static is initialized once, safely.
// CV hook: a single config / connection-pool handle.
#include <bits/stdc++.h>
using namespace std;

class Config {
    map<string,string> kv;
    Config(){ kv["env"]="prod"; }                 // private ctor
public:
    Config(const Config&) = delete;               // no copies
    Config& operator=(const Config&) = delete;
    static Config& instance(){ static Config c; return c; } // thread-safe lazy init
    string get(const string& k){ return kv[k]; }
};
int main(){
    cout << Config::instance().get("env") << "\n"; // prod
    cout << (&Config::instance()==&Config::instance() ? "same instance" : "DIFFERENT") << "\n";
}
