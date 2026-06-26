// Proxy — a stand-in that controls access to a real object (lazy-load, auth, cache, remote).
// Same interface as the real subject. vs Decorator: decorator adds features; proxy guards access.
#include <bits/stdc++.h>
using namespace std;

struct Image { virtual void display() = 0; virtual ~Image()=default; };
struct RealImage : Image {
    string file;
    explicit RealImage(string f): file(move(f)) { cout << "loading " << file << " from disk\n"; } // costly
    void display() override { cout << "showing " << file << "\n"; }
};
struct ProxyImage : Image {                          // defers the costly load until needed
    string file; RealImage* real=nullptr;
    explicit ProxyImage(string f): file(move(f)) {}
    void display() override { if(!real) real=new RealImage(file); real->display(); } // lazy
};
int main(){
    ProxyImage img("photo.png");                      // no disk load yet
    cout << "proxy created\n";
    img.display();                                    // loads now, then shows
    img.display();                                    // reuses, no reload
}
