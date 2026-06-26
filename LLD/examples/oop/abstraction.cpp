// Abstraction — expose WHAT (interface), hide HOW (implementation).
// When: callers should depend on a capability, not a concrete type.
// UML: <<abstract>> Shape { +area()* } <|-- Circle, Rectangle
#include <bits/stdc++.h>
using namespace std;

struct Shape {                              // abstract: pure virtual = no impl, must override
    virtual double area() const = 0;
    virtual ~Shape() = default;
};
struct Circle : Shape {
    double r; Circle(double rr):r(rr){}
    double area() const override { return 3.14159 * r * r; }
};
struct Rectangle : Shape {
    double w,h; Rectangle(double ww,double hh):w(ww),h(hh){}
    double area() const override { return w * h; }
};

double totalArea(const vector<Shape*>& shapes){ // works for ANY shape, present or future
    double t=0; for (auto s: shapes) t += s->area(); return t;
}
int main(){
    vector<Shape*> shapes = { new Circle(2), new Rectangle(3,4) };
    cout << "total area = " << totalArea(shapes) << "\n"; // ~24.566
}
