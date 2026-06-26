// Memento — capture and restore an object's state without exposing its internals (undo/snapshots).
// The originator creates/uses mementos; a caretaker stores them.
#include <bits/stdc++.h>
using namespace std;

class Memento {                                       // opaque snapshot
    string state; friend class Editor;
    explicit Memento(string s): state(move(s)) {}
};
class Editor {                                        // originator
    string content;
public:
    void type(const string& t){ content += t; }
    string text() const { return content; }
    Memento save() const { return Memento(content); }       // snapshot
    void restore(const Memento& m){ content = m.state; }    // rollback
};
int main(){
    Editor e; e.type("hello");
    Memento snap = e.save();                          // checkpoint
    e.type(" world"); cout<<e.text()<<"\n";          // hello world
    e.restore(snap);  cout<<e.text()<<"\n";          // hello  (restored)
}
