// Pub-Sub System - machine-coding stub (C++, target 45 min, Observer).
#include <bits/stdc++.h>
using namespace std;
struct Subscriber {
    string id; vector<string> inbox;
    void receive(const string& msg){ inbox.push_back(msg); }
};
class Broker {
    unordered_map<string, vector<Subscriber*>> topics;  // topic -> subscribers
public:
    void subscribe(const string& topic, Subscriber* s){
        // TODO: add s to topic's subscriber list (no duplicates)
        throw logic_error("TODO");
    }
    void unsubscribe(const string& topic, Subscriber* s){
        // TODO: remove s from topic
        throw logic_error("TODO");
    }
    void publish(const string& topic, const string& msg){
        // TODO: deliver msg to all subscribers of topic
        throw logic_error("TODO");
    }
};
int main(){
    Broker b; Subscriber a{"a"}, c{"c"};
    b.subscribe("sports",&a); b.subscribe("sports",&c); b.subscribe("tech",&a);
    b.publish("sports","goal!"); b.publish("tech","new chip");
    assert(a.inbox.size()==2 && c.inbox.size()==1);
    b.unsubscribe("sports",&c); b.publish("sports","again");
    assert(c.inbox.size()==1);
    cout<<"PASS\n";
}
// PASSING: per-topic fan-out, subscribe/unsubscribe, no delivery after unsubscribe (Observer).
