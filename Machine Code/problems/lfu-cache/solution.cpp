// LFU Cache - machine-coding stub (C++, target 45 min).
#include <bits/stdc++.h>
using namespace std;
class LFUCache {
    int cap, minFreq=0;
    unordered_map<int,int> val, freq;
    unordered_map<int, list<int>> buckets;                 // freq -> keys (LRU front->back)
    unordered_map<int, list<int>::iterator> pos;
    void bump(int key){
        // TODO: move key from freq f bucket to f+1; update minFreq if needed
        throw logic_error("TODO");
    }
public:
    LFUCache(int capacity): cap(capacity) {}
    int get(int key){
        // TODO: if present, bump, return val; else -1
        throw logic_error("TODO");
    }
    void put(int key,int value){
        // TODO: update existing (bump); else evict minFreq LRU if full; insert freq=1
        throw logic_error("TODO");
    }
};
int main(){
    LFUCache c(2);
    c.put(1,1); c.put(2,2);
    assert(c.get(1)==1);   // freq1=2, freq2=1
    c.put(3,3);            // evict key2
    assert(c.get(2)==-1 && c.get(3)==3);
    cout<<"PASS\n";
}
// PASSING: evict least-frequent; ties by LRU; get/put both raise frequency.
