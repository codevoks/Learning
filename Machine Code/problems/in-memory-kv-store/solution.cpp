// In-memory KV Store - machine-coding stub (C++, target 45 min).
#include <bits/stdc++.h>
using namespace std;
class KVStore {
    struct Val { string v; double expireAt; bool hasTtl; };
    unordered_map<string,Val> data;
    function<double()> now;
    vector<unordered_map<string,Val>> txStack;   // snapshots
public:
    KVStore(function<double()> clock=[]{return 0.0;}): now(move(clock)) {}
    void set(const string& k,const string& v, double ttl=-1){
        // TODO: store value; expireAt=now()+ttl if ttl>=0
        throw logic_error("TODO");
    }
    optional<string> get(const string& k){
        // TODO: return value if present & not expired (purge if expired) else nullopt
        throw logic_error("TODO");
    }
    void del(const string& k){ data.erase(k); }
    void begin(){ txStack.push_back(data); }       // snapshot
    void rollback(){ /* TODO: restore last snapshot */ throw logic_error("TODO"); }
    void commit(){ /* TODO: drop last snapshot (changes persist) */ throw logic_error("TODO"); }
};
int main(){
    double t=0.0; KVStore kv([&]{return t;});
    kv.set("a","1",10); assert(kv.get("a")==optional<string>("1"));
    t=11; assert(kv.get("a")==nullopt);            // expired
    kv.set("b","x"); kv.begin(); kv.set("b","y"); kv.rollback();
    assert(kv.get("b")==optional<string>("x"));    // rolled back
    cout<<"PASS\n";
}
// PASSING: TTL expiry, rollback restores, commit persists, clock injected.
