// Runtime polymorphism: base pointer -> derived method via vtable.
#include <bits/stdc++.h>
using namespace std;
struct Shape { virtual double area() const = 0; virtual ~Shape()=default; };
struct Circle : Shape { double r; Circle(double r):r(r){} double area() const override { return 3.14159*r*r; } };
struct Square : Shape { double s; Square(double s):s(s){} double area() const override { return s*s; } };
int main(){
    vector<unique_ptr<Shape>> shapes;
    shapes.push_back(make_unique<Circle>(2));
    shapes.push_back(make_unique<Square>(3));
    double total=0;
    for(auto& s : shapes) total += s->area();   // each call dispatches via vptr->vtable
    cout<<"total="<<total<<"\n";                 // ~12.566 + 9
}
// Non-virtual call would bind by static type (Shape) at compile time.
