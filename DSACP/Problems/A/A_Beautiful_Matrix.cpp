#include<bits/stdc++.h>
using namespace std;
using lli = long long;
#define INF 1e18;
const int mod = 1e9+7;

void solve()
{
    lli n = 5;
    lli r,c;
    vector<vector<lli>> m(5,vector<lli>(5));
    for(lli i =0;i<n;i++){
        for(lli j=0;j<n;j++){
            cin>>m[i][j];
            if(m[i][j]){
                r=i;
                c=j;
            }
        }
    }
    int ans = abs(r-2)+abs(c-2);
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
    here the location of 1 can be breakon dowm in terms of row and column (similar to 2D coordinates),
    why I thought that ? Because motion is either along column or row, just like 2D vectors

*/