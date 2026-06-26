// Adapter — make an incompatible interface usable by wrapping it (interface translation).
// vs Decorator: decorator KEEPS the interface and adds behavior; adapter CHANGES the interface.
// Real: wrap a legacy/3rd-party API to fit the interface your code expects.
#include <bits/stdc++.h>
using namespace std;

struct LegacyPrinter { void printUpper(const string& s){ string t=s; for(auto&c:t)c=toupper(c); cout<<t<<"\n"; } };

struct Printer { virtual void print(const string& s) = 0; virtual ~Printer()=default; }; // expected interface
struct PrinterAdapter : Printer {                  // adapts LegacyPrinter -> Printer
    LegacyPrinter& legacy;
    explicit PrinterAdapter(LegacyPrinter& l): legacy(l) {}
    void print(const string& s) override { legacy.printUpper(s); }
};
void clientCode(Printer& p){ p.print("hello"); }   // knows only Printer
int main(){ LegacyPrinter lp; PrinterAdapter a(lp); clientCode(a); } // HELLO
