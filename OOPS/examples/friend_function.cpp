// friend grants access to private members (e.g. operator<< needs ostream on the left).
#include <bits/stdc++.h>
using namespace std;
class Point {
    int x, y;
public:
    Point(int x,int y): x(x), y(y) {}
    friend ostream& operator<<(ostream& os, const Point& p); // friend: sees private x,y
};
ostream& operator<<(ostream& os, const Point& p){ return os<<"("<<p.x<<","<<p.y<<")"; }
int main(){ Point p(3,4); cout<<p<<"\n"; } // (3,4)
// Use friend sparingly — it pierces encapsulation; here it's the idiomatic exception.
