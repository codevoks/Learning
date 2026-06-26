// Vending Machine - LLD starter stub (C++, State pattern).
#include <bits/stdc++.h>
using namespace std;
class VendingMachine;

struct State {
    VendingMachine* m;
    State(VendingMachine* mm):m(mm){}
    virtual void select(const string& code)=0;
    virtual void insert(int amt)=0;
    virtual void dispense()=0;
    virtual ~State()=default;
};

class VendingMachine {
public:
    unordered_map<string,pair<int,int>> inventory; // code -> {price, qty}
    string selected; int balance=0;
    State* state;
    VendingMachine(unordered_map<string,pair<int,int>> inv);
    void select(const string& c){ state->select(c);}
    void insert(int a){ state->insert(a);}
    void dispense(){ state->dispense();}
    void setState(State* s){ state=s; }
};

struct IdleState : State {
    IdleState(VendingMachine* mm):State(mm){}
    void select(const string& code) override {
        // TODO: if item in stock, set selected + move to ItemSelectedState
        throw logic_error("TODO");
    }
    void insert(int) override { throw runtime_error("Select an item first"); }
    void dispense() override { throw runtime_error("Select and pay first"); }
};
// TODO: implement ItemSelectedState, HasMoneyState, DispensingState

VendingMachine::VendingMachine(unordered_map<string,pair<int,int>> inv): inventory(move(inv)) {
    state = new IdleState(this);
}

int main(){
    VendingMachine vm({{"A1",{30,2}}});
    vm.select("A1"); vm.insert(20); vm.insert(10); vm.dispense();
    assert(vm.inventory["A1"].second==1);
    cout<<"PASS\n";
}
// PASSING: illegal action per state throws; dispense only after sufficient pay + change; inventory decrements.
