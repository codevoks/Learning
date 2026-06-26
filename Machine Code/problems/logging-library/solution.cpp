// Logging Library - machine-coding stub (C++, target 30 min).
#include <bits/stdc++.h>
using namespace std;
enum class Level { DEBUG=1, INFO=2, WARN=3, ERROR=4 };
string nm(Level l){switch(l){case Level::DEBUG:return"DEBUG";case Level::INFO:return"INFO";
    case Level::WARN:return"WARN";default:return"ERROR";}}
struct Appender { virtual void write(const string&)=0; virtual ~Appender()=default; };
struct MemoryAppender : Appender {
    vector<string> lines;
    void write(const string& line) override { /* TODO: append */ throw logic_error("TODO"); }
};
class Logger {
    Level minLevel; vector<Appender*> appenders;
public:
    Logger(Level m, vector<Appender*> a): minLevel(m), appenders(move(a)) {}
    void log(Level l,const string& msg){
        // TODO: if l>=minLevel write "["+nm(l)+"] "+msg to all appenders
        throw logic_error("TODO");
    }
};
int main(){
    MemoryAppender mem; Logger lg(Level::INFO, {&mem});
    lg.log(Level::DEBUG,"x"); lg.log(Level::ERROR,"boom");
    assert(mem.lines.size()==1 && mem.lines[0]=="[ERROR] boom");
    cout<<"PASS\n";
}
// PASSING: level filtering, multi-appender fan-out, OCP for new appenders.
