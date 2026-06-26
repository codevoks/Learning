// Cab Booking (Uber/Ola) - LLD starter stub (C++).
#include <bits/stdc++.h>
using namespace std;
enum class TripStatus { REQUESTED, ASSIGNED, ONGOING, COMPLETED };

struct Driver { string id; int location; bool available=true; };

struct PricingStrategy { // surge-able
    virtual double fare(double distanceKm) const = 0; virtual ~PricingStrategy()=default;
};
struct NormalPricing : PricingStrategy {
    double fare(double km) const override {
        // TODO: base 50 + 12*km
        throw logic_error("TODO");
    }
};

struct MatchingStrategy {
    virtual Driver* match(vector<Driver>& drivers, int riderLoc) const = 0; virtual ~MatchingStrategy()=default;
};
struct NearestDriver : MatchingStrategy {
    Driver* match(vector<Driver>& drivers, int riderLoc) const override {
        // TODO: nearest AVAILABLE driver to riderLoc, else nullptr
        throw logic_error("TODO");
    }
};

struct Trip { string id; int riderLoc; double distanceKm; TripStatus status=TripStatus::REQUESTED; Driver* driver=nullptr; double fare=0; };

class CabService {
    vector<Driver> drivers; MatchingStrategy* matcher; PricingStrategy* pricer;
public:
    CabService(vector<Driver> d, MatchingStrategy* m, PricingStrategy* p): drivers(move(d)), matcher(m), pricer(p) {}
    Driver* requestRide(Trip& t){
        // TODO: match a driver, mark unavailable, set status ASSIGNED + fare via pricer
        throw logic_error("TODO");
    }
    void completeTrip(Trip& t){
        // TODO: status COMPLETED, free the driver
        throw logic_error("TODO");
    }
};

int main(){
    CabService svc({{"D1",10},{"D2",3}}, new NearestDriver(), new NormalPricing());
    Trip t{"T1", 4, 10.0};
    Driver* d = svc.requestRide(t);
    assert(d && d->id=="D2");          // nearest to loc 4
    assert(t.status==TripStatus::ASSIGNED);
    assert((long)llround(t.fare)==170); // 50 + 12*10
    svc.completeTrip(t);
    assert(t.status==TripStatus::COMPLETED);
    cout<<"PASS\n";
}
// PASSING: nearest available driver matched; fare via pricing strategy; trip state transitions; swap matching/pricing without CabService change (OCP).
