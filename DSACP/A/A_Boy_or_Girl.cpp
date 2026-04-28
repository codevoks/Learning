#include<bits/stdc++.h>
using namespace std;
using lli = long long;
#define INF 1e18;
const int mod = 1e9+7;

lli numberOfDistinctCharacters(string s){
    unordered_map<char,lli> ump;
    for(lli i = 0;i<s.length();i++){
        ump[s[i]]++;
    }
    return ump.size();
}

void solve()
{
    string username;
    cin>>username;
    lli numOfDistChar = numberOfDistinctCharacters(username);
    string ans = numOfDistChar%2?"IGNORE HIM!":"CHAT WITH HER!";
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