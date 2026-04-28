#include<bits/stdc++.h>
using namespace std;
using lli = long long;
#define INF 1e9;
const int mod = 1e9+7;

void solve(){
    lli n,m;
    cin>>n>>m;
    vector<lli> a;
    for(lli i=0;i<n;i++){
        lli price;
        cin>>price;
        a.push_back(price);
    }
    sort(a.begin(),a.end());
    lli ans=0;
    for(lli i=0;i<m;i++){
        if(a[i]<0){
            ans+=abs(a[i]);
        }
    }
    cout<<ans<<"\n";
}

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int _t=1;
    // cin>>_t;
    while(_t--){
        solve();
    }
}