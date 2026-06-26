// Factory Method — defer object creation to a function/subclass so callers don't `new` concretes.
// Decouples client from concrete types -> open for new products (OCP).
// vs Abstract Factory: this makes ONE product; abstract factory makes FAMILIES.
#include <bits/stdc++.h>
using namespace std;

struct Shape { virtual string name() const = 0; virtual ~Shape()=default; };
struct Circle : Shape { string name() const override { return "circle"; } };
struct Square : Shape { string name() const override { return "square"; } };

struct ShapeFactory {                              // central creation point
    static unique_ptr<Shape> create(const string& type){
        if (type=="circle") return make_unique<Circle>();
        if (type=="square") return make_unique<Square>();
        throw invalid_argument("unknown shape");
    }
};
int main(){
    auto s = ShapeFactory::create("circle");
    cout << s->name() << "\n";                      // circle  (client never wrote `new Circle`)
}
