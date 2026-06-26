// Food Delivery - LLD starter stub (C++).
#include <bits/stdc++.h>
using namespace std;
enum class OrderStatus { PLACED, ACCEPTED, PREPARING, OUT_FOR_DELIVERY, DELIVERED };

struct Rider { string id; int location; int activeOrders=0; };

struct AssignmentStrategy {
    virtual Rider* assign(vector<Rider>& riders, int restaurantLoc) const = 0;
    virtual ~AssignmentStrategy()=default;
};
struct NearestRider : AssignmentStrategy {
    Rider* assign(vector<Rider>& riders, int restaurantLoc) const override {
        // TODO: return rider closest to restaurantLoc (prefer free)
        throw logic_error("TODO");
    }
};

struct Order { string id; int restaurantLoc; OrderStatus status=OrderStatus::PLACED; Rider* rider=nullptr; };

class FoodDeliveryApp {
    vector<Rider> riders; AssignmentStrategy* strat;
public:
    FoodDeliveryApp(vector<Rider> r, AssignmentStrategy* s): riders(move(r)), strat(s) {}
    Rider* assignRider(Order& o){
        // TODO: use strategy; set o.rider; rider.activeOrders++; advance status
        throw logic_error("TODO");
    }
};

int main(){
    FoodDeliveryApp app({{"R1",10},{"R2",2}}, new NearestRider());
    Order o{"O1",3};
    Rider* r = app.assignRider(o);
    assert(r->id=="R2"); // closer to loc 3
    cout<<"PASS\n";
}
// PASSING: assignment via strategy; order gets rider + status advances; swap strategy without app change.
