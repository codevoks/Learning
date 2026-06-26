// ATM - LLD starter stub (C++, State pattern).
#include <bits/stdc++.h>
using namespace std;
class ATM;

struct Account { string pin; int balance; };

struct ATMState {
    ATM* atm; ATMState(ATM* a):atm(a){}
    virtual void insertCard(Account* acc)=0;
    virtual void enterPin(const string& pin)=0;
    virtual void withdraw(int amount)=0;
    virtual ~ATMState()=default;
};

class ATM {
public:
    int cash; Account* account=nullptr; ATMState* state;
    ATM(int c);
    void insertCard(Account* a){ state->insertCard(a); }
    void enterPin(const string& p){ state->enterPin(p); }
    void withdraw(int a){ state->withdraw(a); }
    void setState(ATMState* s){ state=s; }
};

struct IdleState : ATMState {
    IdleState(ATM* a):ATMState(a){}
    void insertCard(Account* acc) override {
        // TODO: set account, move to CardInsertedState
        throw logic_error("TODO");
    }
    void enterPin(const string&) override { throw runtime_error("Insert card first"); }
    void withdraw(int) override { throw runtime_error("Insert card first"); }
};
// TODO: CardInsertedState (enterPin), AuthenticatedState (withdraw)

ATM::ATM(int c): cash(c) { state = new IdleState(this); }

int main(){
    ATM atm(10000);
    Account acc{"1234",500};
    atm.insertCard(&acc); atm.enterPin("1234"); atm.withdraw(300);
    assert(acc.balance==200 && atm.cash==9700);
    cout<<"PASS\n";
}
// PASSING: wrong PIN rejected; illegal action per state throws; withdraw checks balance AND atm cash.
