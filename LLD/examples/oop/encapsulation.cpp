// Encapsulation — bundle data + behavior, hide internals, protect invariants.
// When: always; the default for any class holding state.
// CV hook: ledger balance must never go invalid — invariants live inside the class.
// UML: BankAccount { -balance : double | +deposit(); +withdraw(); +getBalance() }
#include <bits/stdc++.h>
using namespace std;

class BankAccount {
    double balance;                         // private: nobody outside can corrupt it
public:
    explicit BankAccount(double opening): balance(opening) {
        if (opening < 0) throw invalid_argument("opening < 0");
    }
    void deposit(double amt) {
        if (amt <= 0) throw invalid_argument("deposit must be > 0");
        balance += amt;
    }
    void withdraw(double amt) {
        if (amt <= 0) throw invalid_argument("withdraw must be > 0");
        if (amt > balance) throw runtime_error("insufficient funds"); // invariant guarded here
        balance -= amt;
    }
    double getBalance() const { return balance; }   // read-only access
};

int main(){
    BankAccount a(100);
    a.deposit(50); a.withdraw(30);
    cout << "balance = " << a.getBalance() << "\n";   // 120
    try { a.withdraw(1000); } catch (exception& e) { cout << "blocked: " << e.what() << "\n"; }
}
