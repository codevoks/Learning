// Iterator — traverse a collection without exposing its internal representation.
// (C++'s STL iterators are this pattern.) Here: a custom range over a tree-ish container.
#include <bits/stdc++.h>
using namespace std;

class IntBag {
    vector<int> data;
public:
    void add(int x){ data.push_back(x); }
    // expose iteration via begin/end (the iterator interface) without revealing the vector
    vector<int>::const_iterator begin() const { return data.begin(); }
    vector<int>::const_iterator end()   const { return data.end(); }
};
int main(){
    IntBag bag; bag.add(1); bag.add(2); bag.add(3);
    int sum=0; for(int x : bag) sum+=x;              // range-for uses begin()/end()
    cout<<"sum="<<sum<<"\n";                         // 6  (client never sees the vector)
}
