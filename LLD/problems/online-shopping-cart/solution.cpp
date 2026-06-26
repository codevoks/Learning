// Online Shopping Cart (Amazon) - LLD starter stub (C++).
#include <bits/stdc++.h>
using namespace std;

struct Product { string id; string name; double price; };

struct DiscountStrategy { virtual double apply(double subtotal) const = 0; virtual ~DiscountStrategy()=default; };
struct NoDiscount : DiscountStrategy { double apply(double s) const override { return s; } };
struct PercentOff : DiscountStrategy {
    double pct; PercentOff(double p):pct(p){}
    double apply(double s) const override {
        // TODO: s * (1 - pct/100)
        throw logic_error("TODO");
    }
};

struct PaymentStrategy { virtual bool pay(double amount) const = 0; virtual ~PaymentStrategy()=default; };
struct CardPayment : PaymentStrategy { bool pay(double) const override { return true; } };

class Cart {
    map<string,int> items;                  // productId -> qty
    unordered_map<string,Product> catalog;
public:
    Cart(vector<Product> products){ for(auto& p:products) catalog[p.id]=p; }
    void add(const string& pid, int qty){
        // TODO: validate product exists; add qty
        throw logic_error("TODO");
    }
    void remove(const string& pid){ items.erase(pid); }
    double subtotal(){
        // TODO: sum price*qty over items
        throw logic_error("TODO");
    }
    double checkout(const DiscountStrategy& disc, const PaymentStrategy& pay){
        // TODO: total = disc.apply(subtotal()); if pay.pay(total) return total; else throw
        throw logic_error("TODO");
    }
};

int main(){
    Cart c({{"p1","Book",100},{"p2","Pen",20}});
    c.add("p1",2); c.add("p2",3);            // 200 + 60 = 260
    assert((long)llround(c.subtotal())==260);
    PercentOff ten(10); CardPayment card;
    assert((long)llround(c.checkout(ten,card))==234); // 10% off
    cout<<"PASS\n";
}
// PASSING: add/remove/subtotal correct; discount + payment via strategies; new discount/payment without Cart change (OCP).
