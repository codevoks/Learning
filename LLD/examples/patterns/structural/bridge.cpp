// Bridge — decouple an abstraction from its implementation so the two vary independently.
// Avoids a class explosion when you have TWO dimensions (e.g. ShapeType x RenderAPI).
// Abstraction holds a pointer to an Implementor.
#include <bits/stdc++.h>
using namespace std;

struct Renderer { virtual string draw(const string& shape) const = 0; virtual ~Renderer()=default; }; // implementor
struct VectorRenderer : Renderer { string draw(const string& s) const override { return "vector "+s; } };
struct RasterRenderer : Renderer { string draw(const string& s) const override { return "raster "+s; } };

struct Shape {                                        // abstraction
    Renderer& r; explicit Shape(Renderer& rr): r(rr) {}
    virtual string render() const = 0; virtual ~Shape()=default;
};
struct Circle : Shape { using Shape::Shape; string render() const override { return r.draw("circle"); } };
struct Square : Shape { using Shape::Shape; string render() const override { return r.draw("square"); } };

int main(){
    VectorRenderer v; RasterRenderer ra;
    cout << Circle(v).render() << "\n";               // vector circle
    cout << Square(ra).render() << "\n";              // raster square  (2 axes vary independently)
}
