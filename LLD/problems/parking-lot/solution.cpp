// Parking Lot - LLD starter stub (C++). Complete the TODOs.
// Build: g++ -std=c++17 solution.cpp -o sol && ./sol
#include <bits/stdc++.h>
using namespace std;

enum class SpotSize { SMALL, MEDIUM, LARGE };

struct Vehicle { string plate; SpotSize size; };

struct PricingStrategy {
    virtual double price(int hours, SpotSize s) const = 0;
    virtual ~PricingStrategy() = default;
};
struct HourlyPricing : PricingStrategy {
    double price(int hours, SpotSize s) const override {
        // TODO: rate per size * hours  (SMALL 10, MEDIUM 20, LARGE 30)
        throw logic_error("TODO");
    }
};

struct Spot {
    string id; SpotSize size; Vehicle* vehicle = nullptr;
    bool isFree() const { return vehicle == nullptr; }
    bool canFit(const Vehicle& v) const {
        // TODO: a vehicle fits a spot of equal-or-larger size
        throw logic_error("TODO");
    }
};

class ParkingLot {
    vector<Spot> spots; PricingStrategy* pricing;
    unordered_map<string,int> active; // plate -> spot index (entry tracked elsewhere)
public:
    ParkingLot(vector<Spot> s, PricingStrategy* p): spots(move(s)), pricing(p) {}
    Spot* park(Vehicle& v) {
        // TODO: find nearest free fitting spot, occupy, return it (or nullptr if full)
        throw logic_error("TODO");
    }
    double unpark(const string& plate, int hours) {
        // TODO: free the spot, return fee via pricing strategy
        throw logic_error("TODO");
    }
};

int main(){
    HourlyPricing hp;
    vector<Spot> spots = {{"S1",SpotSize::SMALL},{"M1",SpotSize::MEDIUM}};
    ParkingLot lot(spots,&hp);
    Vehicle v{"KA01",SpotSize::SMALL};
    Spot* s = lot.park(v); assert(s);
    assert(lot.unpark("KA01",2)==20); // 2h*10
    cout<<"PASS\n";
}
// PASSING: park assigns fitting free spot; unpark returns correct fee; new PricingStrategy needs no ParkingLot change (OCP).
