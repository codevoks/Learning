#include<bits/stdc++.h>
using namespace std;
using lli = long long;
#define INF 1e9
const lli mod = 1e9+7;

lli lastDigit(lli num){
    return num%10;
}

void solve(){
    lli n,k;
    cin>>n>>k;
    while(k--){
        if(!lastDigit(n)){a
            n/=10;
        }else{
            n--;
        }
    }
    cout<<n<<"\n";
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