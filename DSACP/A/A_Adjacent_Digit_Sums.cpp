#include<bits/stdc++.h>
using namespace std;
using lli = long long;
#define INF 1e18;
const int mod = 1e9+7;

void solve()
{
    lli x,y;
    cin>>x>>y;
    string ans;
    if(x>y){
        ans = ((x-y+1)%9)?"Yes":"No";
    }
    else if(x<y){
        ans = ((y-x)==1)?"Yes":"No";
    }
    else{
        ans = "No";
    }
    cout<<ans<<'\n';
}

signed main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int _t=1;
    cin>>_t;
    while(_t--)
    {
        solve();
    }
}

/*
 No. of testcases 1≤TC≤500
 Given x,y (1≤x,y≤1000)
 we have to find n such that S(n): sum of digite of n is such that
 S(n) = x
 S(n+1) = y

 Case 1: x > y (Sum is reduced)
 This only possible when there is a series of p(p>0) consecutive 9's in the end
 In this case the contribution of those p 9's in the sum of digits reduces to 1
 hence if x = S(n)
 y = S(n)-9p+1
 p = (x-y+1)/9

 Case 2: x < y (Sum is increased)
 The sum in case of two consecutive numbers the sum of digits can increase by 1 at most
 So y-x = 1 for this to be possible
*/