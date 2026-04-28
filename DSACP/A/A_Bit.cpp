#include<bits/stdc++.h>
using namespace std;
using lli = long long;
#define INF 1e18;
const int mod = 1e9+7;

bool checkPlus(string statement){
    return statement.find("+")!=string::npos;
}

void solve()
{
    lli n,x=0;
    cin>>n;
    for(lli i=1;i<=n;i++){
        string statement;
        cin>>statement;
        bool inc = checkPlus(statement);
        if(inc){
            x++;
        }
        else{
            x--;
        }
    }
    lli ans=x;
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
just check if sy bol '+' is used to know when to add and subtract otherwise
*/