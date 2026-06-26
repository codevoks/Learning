// Hotel Booking - LLD starter stub (C++).
#include <bits/stdc++.h>
using namespace std;

struct Room { string id; string type; }; // e.g. DELUXE

struct PricingStrategy { virtual double price(const string& type, int nights) const = 0; virtual ~PricingStrategy()=default; };
struct FlatPricing : PricingStrategy {
    double price(const string& type, int nights) const override {
        // TODO: rate per type (STANDARD 2000, DELUXE 4000) * nights
        throw logic_error("TODO");
    }
};

struct Booking { string roomId; int checkIn, checkOut; }; // day numbers

class Hotel {
    vector<Room> rooms; PricingStrategy* pricer;
    map<string, vector<Booking>> byRoom;
public:
    Hotel(vector<Room> r, PricingStrategy* p): rooms(move(r)), pricer(p) {}
    // returns roomId booked or "" if none available of type for [in,out)
    string book(const string& type, int in, int out){
        // TODO: find a room of type whose existing bookings don't overlap [in,out); record + return id
        throw logic_error("TODO");
    }
    double quote(const string& type, int in, int out){ return pricer->price(type, out-in); }
};

int main(){
    Hotel h({{"R1","DELUXE"},{"R2","DELUXE"}}, new FlatPricing());
    assert(h.book("DELUXE",1,3)=="R1");
    assert(h.book("DELUXE",2,4)=="R2");   // R1 overlaps -> next room
    assert(h.book("DELUXE",1,2)=="");     // both busy on day1
    assert((long)llround(h.quote("DELUXE",1,3))==8000); // 2 nights *4000
    cout<<"PASS\n";
}
// PASSING: no overlapping bookings per room; falls back to another room of type; pricing via strategy.
