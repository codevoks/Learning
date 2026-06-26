// Notification Service - machine-coding stub (C++, target 45 min).
#include <bits/stdc++.h>
using namespace std;
struct Channel { virtual bool send(const string& user,const string& msg)=0; virtual ~Channel()=default; };
struct FlakyChannel : Channel {
    int failTimes; vector<string> sent; int calls=0;
    FlakyChannel(int f):failTimes(f){}
    bool send(const string& user,const string& msg) override {
        // TODO: fail (false) first failTimes calls, then record+true
        throw logic_error("TODO");
    }
};
class NotificationService {
    unordered_map<string,Channel*> channels; int maxRetries; set<string> seen;
public:
    NotificationService(unordered_map<string,Channel*> ch,int retries=3): channels(move(ch)), maxRetries(retries) {}
    bool notify(const string& user,const string& msg,const string& channel,const string& idemKey){
        // TODO: if idemKey seen -> true (dedup, no resend);
        // else try channel.send up to maxRetries; on success mark seen + true; else false
        throw logic_error("TODO");
    }
};
int main(){
    FlakyChannel* ch=new FlakyChannel(2);
    NotificationService svc({{"email",ch}},3);
    assert(svc.notify("u","hi","email","k1")==true);  // succeeds on 3rd try
    assert(ch->sent.size()==1);
    assert(svc.notify("u","hi","email","k1")==true);  // dedup, no new send
    assert(ch->sent.size()==1);
    cout<<"PASS\n";
}
// PASSING: dedup by idemKey, retry up to max then fail, OCP for new channels.
