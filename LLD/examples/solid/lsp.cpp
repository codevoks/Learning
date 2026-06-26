// LSP — Liskov Substitution: a subtype must be usable wherever the base is, without surprises.
// CLASSIC VIOLATION: Square : Rectangle. Setting width also changes height, breaking code that
//   expects Rectangle's contract (set w=5,h=4 -> area 20). So Square is NOT a behavioral Rectangle.
// FIX: don't force the bad is-a; model a common Shape abstraction instead.
#include <bits/stdc++.h>
using namespace std;

struct Shape { virtual int area() const = 0; virtual ~Shape()=default; };
struct Rectangle : Shape {
    int w,h; Rectangle(int ww,int hh):w(ww),h(hh){}
    int area() const override { return w*h; }
};
struct Square : Shape {                       // sibling, not subclass of Rectangle
    int side; explicit Square(int s):side(s){}
    int area() const override { return side*side; }
};
int totalArea(const vector<Shape*>& v){ int t=0; for(auto s:v) t+=s->area(); return t; }
int main(){
    vector<Shape*> shapes = { new Rectangle(5,4), new Square(3) };
    cout << "area = " << totalArea(shapes) << "\n"; // 20 + 9 = 29; every subtype honors the contract
}
