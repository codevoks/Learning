// Composite — treat individual objects and groups uniformly via a common interface (tree).
// Real: file system (file vs folder), UI groups, org charts. Client doesn't care leaf vs branch.
#include <bits/stdc++.h>
using namespace std;

struct Node { virtual int size() const = 0; virtual ~Node()=default; }; // common interface
struct File : Node { int bytes; explicit File(int b):bytes(b){} int size() const override { return bytes; } };
struct Folder : Node {                               // a Folder is also a Node (holds Nodes)
    vector<Node*> children;
    void add(Node* n){ children.push_back(n); }
    int size() const override { int t=0; for(auto c:children) t+=c->size(); return t; } // recurse
};
int main(){
    Folder root; root.add(new File(100));
    Folder sub; sub.add(new File(50)); sub.add(new File(25));
    root.add(&sub);
    cout << "total = " << root.size() << "\n";        // 175 (leaf + branch treated the same)
}
