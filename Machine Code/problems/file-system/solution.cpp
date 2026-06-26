// In-memory File System - machine-coding stub (C++, target 60 min).
#include <bits/stdc++.h>
using namespace std;
struct Node {
    bool isFile=false; string content;
    map<string,Node*> children;
};
class FileSystem {
    Node* root = new Node();
    Node* walk(const string& path, bool create){
        // TODO: split path by '/', traverse (create dirs if create), return node
        throw logic_error("TODO");
    }
public:
    void mkdir(const string& path){ /* TODO: create dirs along path */ throw logic_error("TODO"); }
    void addContent(const string& path,const string& content){
        // TODO: create file if missing, append content
        throw logic_error("TODO");
    }
    string read(const string& path){ /* TODO */ throw logic_error("TODO"); }
    vector<string> ls(const string& path){
        // TODO: if file -> [filename]; if dir -> sorted child names
        throw logic_error("TODO");
    }
};
int main(){
    FileSystem fs;
    fs.mkdir("/a/b");
    fs.addContent("/a/b/f.txt","hello");
    fs.addContent("/a/b/f.txt"," world");
    assert(fs.read("/a/b/f.txt")=="hello world");
    assert((fs.ls("/a/b")==vector<string>{"f.txt"}));
    assert((fs.ls("/a")==vector<string>{"b"}));
    cout<<"PASS\n";
}
// PASSING: nested mkdir, append semantics, ls sorted, read returns content.
