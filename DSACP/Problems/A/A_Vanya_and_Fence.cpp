#include<bits/stdc++.h>
using namespace std;
using lli = long long;
#define INF 1e9;
const int mod = 1e9+7;

void solve(){
    lli n,h;
    cin>>n>>h;
    lli ans=0;
    for(lli i=1;i<=n;i++){
        lli a;
        cin>>a;
        ans+=(a<=h?1:2);
    }
    cout<<ans<<"\n";
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int _t=1;
    //cin>>_t;
    while(_t--){
        solve();
    }
}