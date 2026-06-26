// Splitwise - LLD starter stub (C++).
#include <bits/stdc++.h>
using namespace std;

struct SplitStrategy {
    virtual map<string,double> shares(double amt, const vector<string>& parts,
                                      const map<string,double>& meta) const = 0;
    virtual ~SplitStrategy()=default;
};
struct EqualSplit : SplitStrategy {
    map<string,double> shares(double amt, const vector<string>& parts,
                              const map<string,double>&) const override {
        // TODO: divide equally
        throw logic_error("TODO");
    }
};
struct PercentSplit : SplitStrategy {
    map<string,double> shares(double amt, const vector<string>& parts,
                              const map<string,double>& meta) const override {
        // TODO: meta[user]=pct (sum 100); share = amt*pct/100
        throw logic_error("TODO");
    }
};

class Splitwise {
    // balance[a][b] = how much a owes b
    map<string,map<string,double>> balance;
public:
    void addExpense(const string& paidBy, double amt, const vector<string>& parts,
                    const SplitStrategy& strat, const map<string,double>& meta={}) {
        // TODO: compute shares; each participant owes paidBy their share
        throw logic_error("TODO");
    }
    double balanceOf(const string& user) {
        // TODO: net = owed_to_user - user_owes
        throw logic_error("TODO");
    }
};

int main(){
    Splitwise s; EqualSplit eq;
    s.addExpense("A",300,{"A","B","C"},eq);
    assert((long)llround(s.balanceOf("A"))==200);
    assert((long)llround(s.balanceOf("B"))==-100);
    cout<<"PASS\n";
}
// PASSING: EQUAL/PERCENT splits correct; new SplitStrategy needs no Splitwise change; net balances sum to 0.
