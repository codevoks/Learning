// dynamic_cast: safe downcast (nullptr on fail). Prefer virtual over casting when you can.
#include <bits/stdc++.h>
using namespace std;
struct Animal { virtual ~Animal()=default; };
struct Dog : Animal { void bark(){ cout<<"woof\n"; } };
struct Cat : Animal {};
void handle(Animal* a){
    if(Dog* d = dynamic_cast<Dog*>(a)) d->bark();   // succeeds only if a is really a Dog
    else cout<<"not a dog (dynamic_cast -> nullptr)\n";
}
int main(){
    Dog dog; Cat cat;
    handle(&dog);   // woof
    handle(&cat);   // not a dog
}
// static_cast<Dog*>(&cat) would compile but be UB. dynamic_cast checks at runtime.
