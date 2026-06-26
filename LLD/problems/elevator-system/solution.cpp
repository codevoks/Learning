// Elevator System - LLD starter stub (C++).
#include <bits/stdc++.h>
using namespace std;
enum class Direction { UP, DOWN, IDLE };

struct SchedulingStrategy {
    virtual optional<int> nextTarget(int cur, const set<int>& targets, Direction d) const = 0;
    virtual ~SchedulingStrategy() = default;
};
struct NearestStrategy : SchedulingStrategy {
    optional<int> nextTarget(int cur, const set<int>& targets, Direction d) const override {
        // TODO: return closest target floor or nullopt
        throw logic_error("TODO");
    }
};

class Elevator {
    string id; int floor=0; Direction dir=Direction::IDLE;
    set<int> targets; SchedulingStrategy* strat;
public:
    Elevator(string i, SchedulingStrategy* s): id(move(i)), strat(s) {}
    void request(int f){ targets.insert(f); }
    int currentFloor() const { return floor; }
    bool done() const { return targets.empty(); }
    void step(){
        // TODO: ask strategy for next target, move ONE floor toward it,
        // update dir, erase target on arrival
        throw logic_error("TODO");
    }
};

class ElevatorSystem {
    vector<Elevator*> lifts;
public:
    ElevatorSystem(vector<Elevator*> l): lifts(move(l)) {}
    Elevator* dispatch(int floor){
        // TODO: choose best elevator (closest / same direction)
        throw logic_error("TODO");
    }
};

int main(){
    NearestStrategy ns; Elevator e("E1",&ns);
    e.request(3);
    for(int i=0;i<5 && !e.done();++i) e.step();
    assert(e.currentFloor()==3);
    cout<<"PASS\n";
}
// PASSING: elevator reaches requested floor; swapping SchedulingStrategy needs no Elevator change.
