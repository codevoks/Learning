// unique_ptr / shared_ptr / weak_ptr — ownership + breaking cycles.
#include <bits/stdc++.h>
using namespace std;
struct Node {
    int v;
    shared_ptr<Node> next;       // owns next
    weak_ptr<Node>   prev;       // weak -> does NOT keep prev alive (breaks the cycle)
    Node(int v):v(v){ }
    ~Node(){ cout<<"~Node("<<v<<")\n"; }
};
int main(){
    auto u = make_unique<int>(42);          // sole owner
    cout<<"unique="<<*u<<"\n";

    auto a = make_shared<Node>(1);
    auto b = make_shared<Node>(2);
    a->next = b;                              // a owns b
    b->prev = a;                              // weak: no cycle -> both freed at scope end
    cout<<"a.use_count="<<a.use_count()<<"\n"; // 1 (b->prev is weak, doesn't add)
}
// If prev were shared_ptr, a<->b cycle => use_count never 0 => leak. weak_ptr fixes it.
