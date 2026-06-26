// Facade — one simple front door over a complex subsystem. Hides wiring, eases use.
// Doesn't add behavior; just simplifies. Real: an "OrderService.placeOrder()" hiding
// inventory + payment + shipping calls.
#include <bits/stdc++.h>
using namespace std;

struct Inventory { bool reserve(const string& item){ cout<<"reserved "<<item<<"\n"; return true; } };
struct Payment   { bool charge(double amt){ cout<<"charged "<<amt<<"\n"; return true; } };
struct Shipping  { void dispatch(const string& item){ cout<<"shipped "<<item<<"\n"; } };

class OrderFacade {                                  // simple interface over 3 subsystems
    Inventory inv; Payment pay; Shipping ship;
public:
    bool placeOrder(const string& item, double price){
        if (!inv.reserve(item)) return false;
        if (!pay.charge(price)) return false;
        ship.dispatch(item); return true;
    }
};
int main(){ OrderFacade o; o.placeOrder("book", 299); } // client makes ONE call
