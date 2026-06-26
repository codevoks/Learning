// static data member (shared) + static member function (no `this`).
#include <bits/stdc++.h>
using namespace std;
class Widget {
    static int count;          // declaration (shared across all objects)
public:
    Widget(){ ++count; }
    ~Widget(){ --count; }
    static int alive(){ return count; }   // no `this`; call as Widget::alive()
};
int Widget::count = 0;          // definition (outside the class)
int main(){
    Widget a, b;
    { Widget c; cout<<"alive="<<Widget::alive()<<"\n"; } // 3
    cout<<"alive="<<Widget::alive()<<"\n";               // 2 (c destroyed)
}
