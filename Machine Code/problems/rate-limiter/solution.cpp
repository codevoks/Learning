// Rate Limiter (token bucket) - machine-coding stub (C++, target 30 min).
#include <bits/stdc++.h>
using namespace std;
class TokenBucket {
    int capacity; double rate;                 // tokens/sec
    unordered_map<string,double> tokens, last;
public:
    TokenBucket(int cap, double refillPerSec): capacity(cap), rate(refillPerSec) {}
    bool allow(const string& key, double now){
        // TODO: refill by (now-last)*rate capped at capacity; if tokens>=1 consume -> true else false
        throw logic_error("TODO");
    }
};
int main(){
    TokenBucket rl(2,1);
    assert(rl.allow("u",0.0) && rl.allow("u",0.0)); // 2 tokens
    assert(!rl.allow("u",0.0));                       // empty
    assert(rl.allow("u",1.0));                        // refilled 1
    cout<<"PASS\n";
}
// PASSING: bursts up to capacity; denies when empty; refills over time; per-key isolation.
