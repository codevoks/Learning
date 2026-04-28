#include<bits/stdc++.h>
using namespace std;
using lli = long long;
#define INF 1e18;
const int mod = 1e9+7;

void solve()
{
    string s;
    cin>>s;
    vector<lli> num;
    for(lli i=0;i<s.length();i++){
        if(s[i]=='1'){
            num.push_back(1);
        }
        else if(s[i]=='2'){
            num.push_back(2);
        }else if(s[i]=='3'){
            num.push_back(3);
        }
    }
    string ans="";
    sort(num.begin(),num.end());
    for(auto it:num){
        string cur = to_string(it);
        ans+=(cur+"+");
    }
    auto it = ans.rfind("+");
    if(it!=string::npos){
        ans.erase(it,1);
    }
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

*/