// BookMyShow - LLD starter stub (C++, concurrency).
#include <bits/stdc++.h>
#include <mutex>
#include <thread>
using namespace std;

class Show {
public:
    string id; set<string> available, booked; mutex mtx;
    Show(string i, vector<string> seats): id(move(i)), available(seats.begin(),seats.end()) {}
};

class BookingService {
    unordered_map<string, Show*> shows;
public:
    void addShow(Show* s){ shows[s->id]=s; }
    bool book(const string& showId, const vector<string>& seats){
        Show* sh = shows[showId];
        // TODO: lock sh->mtx; verify ALL seats available; if yes move available->booked, return true; else false
        throw logic_error("TODO");
    }
};

int main(){
    BookingService svc;
    svc.addShow(new Show("S1",{"A1","A2","A3"}));
    atomic<int> wins{0};
    vector<thread> ts;
    for(int i=0;i<10;i++) ts.emplace_back([&]{ if(svc.book("S1",{"A1"})) wins++; });
    for(auto& t:ts) t.join();
    assert(wins==1); // exactly one booking wins A1
    cout<<"PASS\n";
}
// PASSING: under concurrency a seat is booked exactly once; partial booking rejected atomically.
