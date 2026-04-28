#include<bits/stdc++.h>
using namespace std;
using lli = long long;
#define INF 1e18;
const int mod = 1e9+7;

void solve()
{
    string s;
    cin>>s;
    lli l = s.length();
    lli ans=0;
    for(lli i =0;i<l;i++){
        if(s[i]=='1'){
            ans++;
        }
    }
    cout<<ans<<'\n';
}

signed main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int _t=1;
    cin>>_t;
    while(_t--)
    {
        solve();
    }
}

/*
    Minimum # of moves ≤ Number of 1's
    Now for each 1 to be reduces we have to include it
    Now if we take equal number of 0's along then the number of 1's remain the same
    Now if we take more 0's than 1 then the number of 1's increase, and so does the upper bound in the first line
    Now if we take more 1' than 0 then the number of 1's decreases by 1
    What is the maximum number of 1's we can reduce ? 
    We can reduce at maximum one 1's at a time
    So the Number of 1's ≤ Minimum # of moves
    So it is a greedy algorithm where we reduce one 1's at a time
*/