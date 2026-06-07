// Last updated: 6/7/2026, 11:26:39 PM
class Solution {
    using lli = long long;
    #define INF 1e18
public:

    lli rec(lli level,lli can_buy,lli k,lli n,vector<vector<vector<lli>>> &dp,vector<int>& prices)
    {
        //pruning

        //base case
        if(level==n)
        {
            return 0;
        }
        //caching
        if(dp[level][can_buy][k]!=-1)
        {
            return dp[level][can_buy][k];
        }
        //transition
        //either buy or sell(not both) or do nothing
        lli ans = -INF;
        //buy
        if(can_buy)
        {
            ans = max(ans,-prices[level]+rec(level+1,0,k,n,dp,prices));
        }
        else if(can_buy==0&&k>0)
        {
            ans = max(ans,prices[level]+rec(level+1,1,k-1,n,dp,prices));
        }
        ans = max(ans,rec(level+1,can_buy,k,n,dp,prices));
        //save and return
        return dp[level][can_buy][k]=ans;
    }

    int maxProfit(int k, vector<int>& prices) {
        lli n = prices.size();
        vector<vector<vector<lli>>> dp(n,vector<vector<lli>>(2,vector<lli>(k+1,-1)));
        lli ans  = rec(0,1,k,n,dp,prices);
        return ans;
    }
};