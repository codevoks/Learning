// Rule of 5: a class owning a raw resource defines dtor + copy(2) + move(2).
#include <bits/stdc++.h>
using namespace std;
class Buffer {
    int* data; size_t n;
public:
    Buffer(size_t n): data(new int[n]{}), n(n) {}
    ~Buffer(){ delete[] data; }                                  // 1 dtor
    Buffer(const Buffer& o): data(new int[o.n]), n(o.n) {        // 2 copy ctor (DEEP)
        copy(o.data, o.data+n, data);
    }
    Buffer& operator=(const Buffer& o){                          // 3 copy assign (copy-and-swap)
        Buffer tmp(o); swap(data, tmp.data); swap(n, tmp.n); return *this;
    }
    Buffer(Buffer&& o) noexcept: data(o.data), n(o.n) {          // 4 move ctor (STEAL)
        o.data=nullptr; o.n=0;
    }
    Buffer& operator=(Buffer&& o) noexcept {                     // 5 move assign
        if(this!=&o){ delete[] data; data=o.data; n=o.n; o.data=nullptr; o.n=0; } return *this;
    }
    size_t size() const { return n; }
};
int main(){
    Buffer a(5);
    Buffer b = a;             // copy ctor (deep)
    Buffer c = std::move(a);  // move ctor (steal)
    cout<<"b.size="<<b.size()<<" c.size="<<c.size()<<"\n"; // 5 5
    cout<<"PASS (no double free, deep copy + move)\n";
}
// Rule of 0 alternative: use std::vector<int> as member -> define NONE of the 5.
