// Task Scheduler - machine-coding stub (C++, target 45 min).
#include <bits/stdc++.h>
using namespace std;
class Scheduler {
    struct Item { double runAt; long seq; function<void()> task; double interval; };
    struct Cmp { bool operator()(const Item&a,const Item&b)const{
        return a.runAt!=b.runAt ? a.runAt>b.runAt : a.seq>b.seq; } };
    priority_queue<Item,vector<Item>,Cmp> pq; long counter=0;
public:
    void schedule(function<void()> task, double runAt, double interval=-1){
        // TODO: push item
        throw logic_error("TODO");
    }
    int runDue(double now){
        // TODO: pop all with runAt<=now, run them, re-schedule recurring; return count executed
        throw logic_error("TODO");
    }
};
int main(){
    vector<string> log; Scheduler s;
    s.schedule([&]{log.push_back("a");},5);
    s.schedule([&]{log.push_back("b");},1);
    s.runDue(2); assert(log.size()==1 && log[0]=="b");
    s.runDue(10); assert(log.size()==2 && log[1]=="a");
    cout<<"PASS\n";
}
// PASSING: runs due tasks in time order; recurring re-schedules; future tasks not run early.
