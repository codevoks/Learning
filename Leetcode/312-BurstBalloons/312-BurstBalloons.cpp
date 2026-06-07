// Last updated: 6/7/2026, 11:26:16 PM
class Solution {
public:
    int rec(int start,int end,vector<int>& nums,int n,vector<vector<int>> &dp)
    {
        if(start>end)
        {
            return 0;
        }
        // if(start==end)
        // {
        //     return nums[start];
        // }
        if(dp[start][end]!=-1)
        {
            return dp[start][end];
        }
        int ans = -1e9;
        for(int i = start;i<=end;i++)
        {
            int a = 1,b =1;
            if(start-1>=0)
            {
                a = nums[start-1];
            }
            if(end+1<n)
            {
                b = nums[end+1];
            }
            ans = max(ans,rec(start,i-1,nums,n,dp) + a*nums[i]*b + rec(i+1,end,nums,n,dp));
        }
        return dp[start][end]=ans;
    }
    int maxCoins(vector<int>& nums) 
    {
        int n = nums.size();
        vector<vector<int>> dp(n,vector<int> (n,-1));
        return rec(0,n-1,nums,n,dp);
    }
};