// Mediator — centralize complex many-to-many comms in one mediator; objects don't ref each other.
// Reduces coupling (n^2 links -> star). e.g. chat room, air-traffic control, UI dialog coordination.
#include <bits/stdc++.h>
using namespace std;
struct User;
struct Mediator { virtual void broadcast(const string& from, const string& msg, User* sender) = 0; virtual ~Mediator()=default; };

struct User {
    string name; Mediator* room;
    User(string n, Mediator* m): name(move(n)), room(m) {}
    void send(const string& msg){ room->broadcast(name, msg, this); }
    void receive(const string& from, const string& msg){ cout<<name<<" got from "<<from<<": "<<msg<<"\n"; }
};
struct ChatRoom : Mediator {
    vector<User*> users;
    void join(User* u){ users.push_back(u); }
    void broadcast(const string& from, const string& msg, User* sender) override {
        for(auto u: users) if(u!=sender) u->receive(from, msg);   // mediator routes
    }
};
int main(){
    ChatRoom room; User a("A",&room), b("B",&room), c("C",&room);
    room.join(&a); room.join(&b); room.join(&c);
    a.send("hi all");                                 // B and C receive; users never reference each other
}
