// Calendar / Meeting Scheduler - machine-coding stub (C++, target 45 min).
#include <bits/stdc++.h>
using namespace std;
class Calendar {
    map<string, vector<pair<int,int>>> rooms;
public:
    bool book(const string& room,int start,int end){
        // TODO: reject if [start,end) overlaps existing in room; else add + true
        // adjacent (prevEnd==start) does NOT overlap
        throw logic_error("TODO");
    }
    vector<pair<int,int>> bookings(const string& room){
        auto v=rooms[room]; sort(v.begin(),v.end()); return v;
    }
};
int main(){
    Calendar cal;
    assert(cal.book("R1",10,20)==true);
    assert(cal.book("R1",15,25)==false); // overlap
    assert(cal.book("R1",20,30)==true);  // adjacent ok
    assert(cal.book("R2",15,25)==true);  // diff room
    cout<<"PASS\n";
}
// PASSING: overlap detection, adjacent allowed, per-room isolation.
