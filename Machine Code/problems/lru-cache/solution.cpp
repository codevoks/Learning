// LRU Cache - machine-coding stub (C++, target 30 min).
#include <bits/stdc++.h>
using namespace std;
class LRUCache {
    int cap; list<pair<int,int>> dll;            // front = MRU
    unordered_map<int, list<pair<int,int>>::iterator> idx;
public:
    LRUCache(int capacity): cap(capacity) {}
    int get(int key){
        // TODO: if present, splice node to front, return value; else -1
        throw logic_error("TODO");
    }
    void put(int key,int value){
        // TODO: update+move-to-front; if over cap, evict back (LRU)
        throw logic_error("TODO");
    }
};
int main(){
    LRUCache c(2);
    c.put(1,1); c.put(2,2);
    assert(c.get(1)==1);
    c.put(3,3); assert(c.get(2)==-1);
    c.put(4,4); assert(c.get(1)==-1 && c.get(3)==3 && c.get(4)==4);
    cout<<"PASS\n";
}
// PASSING: O(1) get/put, correct eviction order, updating existing key refreshes recency.
