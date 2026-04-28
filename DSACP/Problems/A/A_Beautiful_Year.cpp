#include<bits/stdc++.h>
using namespace std;
using lli = long long;
#define INF 1e9;
const int mod = 1e9+7;

lli numberOfDistinctDigits(lli num){
    map<int,int> digitsFrequency;
    while(num){
        lli lastDigit = num%10;
        digitsFrequency[lastDigit]++;
        num/=10;
    }
    return digitsFrequency.size();
}

lli allDigitsDifferent(lli num){
    return numberOfDistinctDigits(num)==4;
}

void solve(){
    lli y;
    cin>>y;
    lli ans=0;
    for(lli i=y+1;i<=10000;i++){
        if(allDigitsDifferent(i)){
            ans=i;
            break;
        }
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