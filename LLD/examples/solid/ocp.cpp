// OCP — Open for extension, Closed for modification.
// VIOLATION: a switch on type means every new discount edits this function.
//   double price(double a,string type){ if(type=="festive")...; else if(type=="member")...; } // BAD
// FIX: a DiscountStrategy interface; add new discounts WITHOUT editing existing code.
#include <bits/stdc++.h>
using namespace std;

struct Discount { virtual double apply(double amt) const = 0; virtual ~Discount()=default; };
struct NoDiscount    : Discount { double apply(double a) const override { return a; } };
struct FestiveOff    : Discount { double apply(double a) const override { return a*0.8; } };
struct MemberOff     : Discount { double apply(double a) const override { return a*0.9; } };
// New "BlackFridayOff" = a new class. Checkout below never changes. <-- OCP

double checkout(double amount, const Discount& d){ return d.apply(amount); }
int main(){
    cout << checkout(1000, FestiveOff()) << "\n";  // 800
    cout << checkout(1000, MemberOff())  << "\n";  // 900
}
