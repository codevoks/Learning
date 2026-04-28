#include<bits/stdc++.h>
using namespace std;
using lli = long long;
#define INF 1e18;
const int mod = 1e9+7;

void solve(){
    lli n,t;
    cin>>n>>t;
    vector<lli> a;
    for(int i = 0;i<n;i++){
        lli temp;
        cin>>temp;
        a.push_back(temp);
    }

    lli ans=0, sum=0;
    lli i = 0,j =0;
    while(j<n){
        sum+=a[j];
        while(sum>t){
            sum-=a[i];
            i++;
        }
        ans=max(ans,j-i+1);
        j++;
    }
    cout<<ans<<"\n";
}

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int _t=1;
    //cin>>_t;
    while(_t--){
        solve();
    }
}