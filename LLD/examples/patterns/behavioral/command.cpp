// Command — encapsulate a request as an object: enables undo/redo, queue, log, macro.
// CV hook: text-editor edits, or queued/replayable operations.
#include <bits/stdc++.h>
using namespace std;

struct Command { virtual void execute() = 0; virtual void undo() = 0; virtual ~Command()=default; };
class Light { public: bool on=false; };
struct LightOn : Command {
    Light& l; explicit LightOn(Light& ll):l(ll){}
    void execute() override { l.on=true; } void undo() override { l.on=false; }
};
class Remote {                                       // invoker with undo history
    vector<Command*> history;
public:
    void press(Command* c){ c->execute(); history.push_back(c); }
    void undoLast(){ if(!history.empty()){ history.back()->undo(); history.pop_back(); } }
};
int main(){
    Light l; Remote r; LightOn cmd(l);
    r.press(&cmd);  cout<<"on? "<<l.on<<"\n";        // 1
    r.undoLast();   cout<<"on? "<<l.on<<"\n";        // 0
}
