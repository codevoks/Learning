#include<bits/stdc++.h>
using namespace std;
using lli = long long;
#define INF 1e18;
const int mod = 1e9+7;

lli count1s(string s){
    lli c=0;
    for(lli i=0;i<s.length();i++){
        if(s[i]=='1'){
            c++;
        }
    }
    return c;
}

void solve()
{
    lli n;
    cin>>n;
    cin.ignore();
    lli ans=0;
    for(lli i=0;i<n;i++){
        string s;
        getline(cin,s);
        lli numberOf1 = count1s(s);
        if(numberOf1>1){
            ans++;
        }
    }
    cout<<ans<<'\n';
}

signed main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int _t=1;
    //cin>>_t;
    while(_t--)
    {
        solve();
    }
}

/*
By default, cin only reads a single word (stops at spaces). To read an entire line including spaces, use getline().
2. Handling getline() After cin

If you’ve used cin before getline(), the newline (\n) left in the buffer will cause getline() to be skipped.

Fix: Clear Input Buffer Before getline()

Use std::cin.ignore():

#include <iostream>
#include <string>

int main() {
    int age;
    std::string name;

    std::cout << "Enter your age: ";
    std::cin >> age;
    
    std::cin.ignore();  // Ignore leftover '\n'
    
    std::cout << "Enter your full name: ";
    std::getline(std::cin, name);

    std::cout << "Age: " << age << ", Name: " << name << std::endl;
    return 0;
}
*/