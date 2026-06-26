// Operator overloading on a value type — only when it reads naturally.
#include <bits/stdc++.h>
using namespace std;
struct Vec2 {
    double x, y;
    Vec2 operator+(const Vec2& o) const { return {x+o.x, y+o.y}; }   // member
    bool  operator==(const Vec2& o) const { return x==o.x && y==o.y; }
};
ostream& operator<<(ostream& os, const Vec2& v){ return os<<"("<<v.x<<","<<v.y<<")"; } // non-member
int main(){
    Vec2 a{1,2}, b{3,4};
    cout<<a+b<<"\n";                       // (4,6)
    cout<<boolalpha<<(a==a)<<" "<<(a==b)<<"\n"; // true false
}
