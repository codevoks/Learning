#include<bits/stdc++.h>
using namespace std;
using lli = long long;
#define INF 1e18;
const int mod = 1e9+7;

int evenCheck(int n){
    return !(n%2);
}

int greaterThan2Check(int n){
    return n>2;
}

void solve()
{
    lli n;
    cin>>n;
    string ans;
    int isEven = evenCheck(n);
    int isGreaterThan2 = greaterThan2Check(n);
    if(isEven&&isGreaterThan2){
        ans = "YES";
    }
    else{
        ans = "NO";
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
    The number of watermelons should be possible to write as sum of two even numbers.
    Sum of two even numbers is always even, what about converse ?
    Divide the even number in two equal -> either even+even or odd+odd
    Now thing is that we habve to give them a +ve number and as 2 is the smallest positive number it won't solve
    basically even number greater than 2 will work
*/