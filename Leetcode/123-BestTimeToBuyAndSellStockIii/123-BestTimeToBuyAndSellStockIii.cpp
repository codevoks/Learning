// Last updated: 6/7/2026, 11:27:07 PM
class Solution {
    using lli = long long;
    #define INF 1e18
public:

    lli rec(lli level,lli can_buy,lli transactions,vector<int>& prices,lli n,vector<vector<vector<lli>>> &dp)
    {
        //pruning

        //base case
        if(level == n)
        {
            return 0;
        }
        //caching
        if(dp[level][can_buy][transactions]!=-1)
        {
            return dp[level][can_buy][transactions];
        }
        //transition
        lli ans = -INF;
        //now we can either buy , sell or do nothing
        //buy
        if(can_buy==1)
        {
            ans = max(ans, 1LL*(-prices[level]+rec(level+1,0,transactions,prices,n,dp)));
        }
        //sell
        else if(can_buy==0&&transactions>0)
        {
            ans = max(ans, 1LL*(prices[level]+ rec(level+1,1,transactions-1,prices,n,dp)));
        }
        //do nothing
        ans = max(ans,1LL*rec(level+1,can_buy,transactions,prices,n,dp));
        //save and return
        return dp[level][can_buy][transactions]= ans;
    }

    int maxProfit(vector<int>& prices) 
    {
        lli n = prices.size();
        lli k = 2;
        vector<vector<vector<lli>>> dp(n,vector<vector<lli>>(2,vector<lli>(k+1,-1)));
        lli ans = rec(0,1,k,prices,n,dp);
        return ans;
    }
};