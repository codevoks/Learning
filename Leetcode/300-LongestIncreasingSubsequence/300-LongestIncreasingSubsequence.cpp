// Last updated: 6/7/2026, 11:26:17 PM
class Solution {
public:
    int f(int ind,int pre,vector<int>& nums,vector<vector<int>> &dp)
    {
        if(ind ==nums.size())
        {
            return 0;
        }
        if(dp[ind][pre+1]!=-1)
        {
            return dp[ind][pre+1];
        }
        int np= f(ind+1,pre,nums,dp);
        if(pre==-1||nums[pre]<nums[ind])
        {
            np=max(np,1+f(ind+1,ind,nums,dp));
        }
        return dp[ind][pre+1]=np;
    }
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> dp(n,vector<int> (n+1,-1));
        return f(0,-1,nums,dp);
    }
};