// DIP — Dependency Inversion: high-level modules depend on ABSTRACTIONS, not concretes.
// VIOLATION: NotificationService { EmailSender email; } -> hard-wired to email, untestable, rigid.
// FIX: depend on an IChannel interface; inject the concrete (dependency injection).
#include <bits/stdc++.h>
using namespace std;

struct IChannel { virtual void send(const string& msg) = 0; virtual ~IChannel()=default; };
struct EmailChannel : IChannel { void send(const string& m) override { cout << "EMAIL: " << m << "\n"; } };
struct SmsChannel   : IChannel { void send(const string& m) override { cout << "SMS: "   << m << "\n"; } };

class NotificationService {                    // high-level: knows only the abstraction
    IChannel& channel;                         // injected, not created here
public:
    explicit NotificationService(IChannel& c): channel(c) {}
    void notify(const string& msg){ channel.send(msg); }
};
int main(){
    EmailChannel email; SmsChannel sms;
    NotificationService viaEmail(email), viaSms(sms);  // swap implementation freely
    viaEmail.notify("hi"); viaSms.notify("hi");
}
