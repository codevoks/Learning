#include<bits/stdc++.h>
using namespace std;
using lli = long long;
#define INF 1e18;
const int mod = 1e9+7;

void solve()
{
    string s;
    cin>>s;
    string ans=s;
    lli l = s.length();
    if(l>10){
        lli m = l-2;
        ans = s[0]+to_string(m)+s[l-1];
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
    
*/