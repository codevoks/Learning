#include<bits/stdc++.h>
using namespace std;
using lli = long long;
#define INF 1e18;
const int mod = 1e9+7;

void solve()
{
    lli n;
    cin>>n;
    unordered_map<lli,lli> a;
    unordered_map<lli,lli> b;
    for(lli i=1;i<=n;i++){
        lli a_i;
        cin>>a_i;
        a[a_i]++;
    }
    for(lli i=1;i<=n;i++){
        lli b_i;
        cin>>b_i;
        b[b_i]++;
    }
    string ans="NO";
    if(a.size()+b.size()>=4){
        ans="YES";
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