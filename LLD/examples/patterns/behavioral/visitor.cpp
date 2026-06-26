// Visitor — add new operations to a class hierarchy WITHOUT modifying the classes (double dispatch).
// Good when the hierarchy is stable but operations change often. Trade-off: adding a new node type
// then touches every visitor.
#include <bits/stdc++.h>
using namespace std;
struct Circle; struct Square;
struct Visitor { virtual void visit(Circle&) = 0; virtual void visit(Square&) = 0; virtual ~Visitor()=default; };

struct Shape { virtual void accept(Visitor& v) = 0; virtual ~Shape()=default; };
struct Circle : Shape { double r=2; void accept(Visitor& v) override { v.visit(*this); } };
struct Square : Shape { double s=3; void accept(Visitor& v) override { v.visit(*this); } };

struct AreaVisitor : Visitor {                        // a new operation, added without editing shapes
    double total=0;
    void visit(Circle& c) override { total += 3.14159*c.r*c.r; }
    void visit(Square& s) override { total += s.s*s.s; }
};
int main(){
    vector<Shape*> shapes = { new Circle(), new Square() };
    AreaVisitor av; for(auto s: shapes) s->accept(av);
    cout<<"total area = "<<av.total<<"\n";            // ~12.566 + 9
}
