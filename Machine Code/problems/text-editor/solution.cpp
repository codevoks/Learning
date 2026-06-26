// Text Editor (undo/redo) - machine-coding stub (C++, target 45 min, Command pattern).
#include <bits/stdc++.h>
using namespace std;
struct Command { virtual void execute(string& doc)=0; virtual void undo(string& doc)=0; virtual ~Command()=default; };
struct InsertCommand : Command {
    int pos; string text;
    InsertCommand(int p,string t):pos(p),text(move(t)){}
    void execute(string& doc) override { /* TODO: insert text at pos */ throw logic_error("TODO"); }
    void undo(string& doc) override { /* TODO: erase the inserted text */ throw logic_error("TODO"); }
};
// (bonus) DeleteCommand
class Editor {
    string doc; vector<Command*> undoStack, redoStack;
public:
    void apply(Command* c){
        // TODO: c->execute(doc); push to undoStack; clear redoStack
        throw logic_error("TODO");
    }
    void undo(){
        // TODO: pop undoStack, c->undo(doc), push to redoStack
        throw logic_error("TODO");
    }
    void redo(){
        // TODO: pop redoStack, c->execute(doc), push to undoStack
        throw logic_error("TODO");
    }
    string text() const { return doc; }
};
int main(){
    Editor e;
    e.apply(new InsertCommand(0,"hello"));
    e.apply(new InsertCommand(5," world"));
    assert(e.text()=="hello world");
    e.undo(); assert(e.text()=="hello");
    e.redo(); assert(e.text()=="hello world");
    cout<<"PASS\n";
}
// PASSING: insert + undo + redo correct; new command types (delete/replace) without editing Editor (Command pattern, OCP).
