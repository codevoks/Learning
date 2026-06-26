// Logging Framework - LLD starter stub (C++, Chain of Responsibility).
#include <bits/stdc++.h>
using namespace std;
enum class Level { DEBUG=1, INFO=2, WARN=3, ERROR=4 };
string name(Level l){ switch(l){case Level::DEBUG:return"DEBUG";case Level::INFO:return"INFO";
    case Level::WARN:return"WARN";default:return"ERROR";} }

struct Appender { virtual void append(Level, const string&)=0; virtual ~Appender()=default; };
struct ConsoleAppender : Appender {
    vector<string> lines;
    void append(Level l, const string& msg) override {
        // TODO: store/print "["+name(l)+"] "+msg
        throw logic_error("TODO");
    }
};

class Logger {
    Level minLevel; vector<Appender*> appenders;
public:
    Logger(Level m, vector<Appender*> a): minLevel(m), appenders(move(a)) {}
    void log(Level l, const string& msg){
        // TODO: if l>=minLevel, dispatch to all appenders
        throw logic_error("TODO");
    }
    void info(const string& m){ log(Level::INFO,m); }
    void error(const string& m){ log(Level::ERROR,m); }
};

int main(){
    ConsoleAppender con;
    Logger lg(Level::INFO, {&con});
    lg.log(Level::DEBUG,"skip"); lg.info("hello"); lg.error("boom");
    assert(con.lines.size()==2); // debug filtered
    cout<<"PASS\n";
}
// PASSING: below-min filtered; multi-appender fan-out; new appender/level without editing Logger (OCP).
