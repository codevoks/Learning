// Last updated: 6/7/2026, 11:27:09 PM
class Solution {
public:
    int rec(int level,int buy,vector<int>& prices,int n,vector<vector<int>> &dp)
    {
        //pruning

        //base case
        if(level==n)
        {
            return 0;
        }
        //caching
        if(dp[level][buy]!=-1)
        {
            return dp[level][buy];
        }
        //transition
        int ans = 0;
        //case 1 buy if we can
        if(buy)
        {
            ans = max(ans,-prices[level]+rec(level+1,0,prices,n,dp));
        }
        //case 2 sell we can't buy and 
        else
        {
            ans = max(ans, prices[level]+rec(level+1,1,prices,n,dp));
        }
        ans = max(ans,rec(level+1,buy,prices,n,dp));
        //save and return
        return dp[level][buy]=ans;
    }
    int maxProfit(vector<int>& prices) 
    {
        int n = prices.size();
        vector<vector<int>> dp(n,vector<int>(2,-1));
        int ans =rec(0,1,prices,n,dp);
        return ans;
    }
};