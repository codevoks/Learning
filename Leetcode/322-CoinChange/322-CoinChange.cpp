// Last updated: 6/7/2026, 11:26:15 PM
class Solution {
public:
    int f(int ind,int amount,vector<int> &coins,vector<vector<int>> &dp)
    {
        if(ind == 0)
        {
            if(amount%coins[0]==0)
            {
                return amount/coins[0];
            }
            else
            {
                return 1e9;
            }
        }
        if(dp[ind][amount]!=-1)
        {
            return dp[ind][amount];
        }
        if(amount==0)
        {
            return 0;
        }
        int np = f(ind-1,amount,coins,dp);
        if(coins[ind]<=amount)
        {
            np = min(np,1+f(ind,amount-coins[ind],coins,dp));
        }
        return dp[ind][amount]=np;
    }
    int coinChange(vector<int>& coins, int amount) {
        vector<vector<int>> dp(coins.size(),vector<int> (amount+1,-1));
        int a= f(coins.size()-1,amount,coins,dp);
        if(a>=1e9)
        {
            return -1;
        }
        return a;
    }
};