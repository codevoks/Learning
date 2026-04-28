#include<bits/stdc++.h>
using namespace std;
using lli = long long;
#define INF 1e9;
const int mod = 1e9+7;

lli isLuckyNumber(lli num){
    lli count4, count7, totalDigits;
    count4 = count7 = totalDigits = 0;
    while(num){
        lli lastDigit=num%10;
        if(lastDigit==4){
            count4++;
        }else if(lastDigit==7){
            count7++;
        }
        totalDigits++;
        num/=10;
    }
    lli do4Or7Exist = (count4+count7)!=0;
    lli doOnly4or7Exist = (count4+count7)==totalDigits;
    return (do4Or7Exist&&doOnly4or7Exist);
}

lli numberOfLuckyDigits(lli num){
    lli luckyDigitCount=0;
    while(num){
        lli lastDigit = num%10;
        if(lastDigit==4 || lastDigit==7){
            luckyDigitCount++;
        }
        num/=10;
    }
    return luckyDigitCount;
}

lli isNearlyLucky(lli num){
    return isLuckyNumber(numberOfLuckyDigits(num));
}

void solve(){
    lli n;
    cin>>n;
    if(isNearlyLucky(n)){
        cout<<"YES"<<"\n";
    }else{
        cout<<"NO"<<"\n";
    }
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