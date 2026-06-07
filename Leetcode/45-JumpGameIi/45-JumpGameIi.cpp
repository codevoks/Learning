// Last updated: 6/7/2026, 11:27:45 PM
class Solution {
public:
    #define INF 1e9
    int rec(int level,int n,vector<int> &nums,vector<int> &dp)
    {
        //pruning

        //base case
        if(level>=n-1)
        {
            return 0;
        }
        //caching
        if(dp[level]!=-1)
        {
            return dp[level];
        }
        //transition
        //we can move at most nums[level steps] and we won't move to spots with 0 maximum moves
        int ans = INF;
        for(int i = 0;i<=nums[level];i++)
        {
            if(i==0)
            {
                continue;
            }
            ans = min(ans,1+rec(level+i,n,nums,dp));
        }
        //save and return
        return dp[level]=ans;
    }

    int jump(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n,-1);
        int ans = rec(0,n,nums,dp);
        if(ans>=INF)
        {
            return -1;
        }
        return ans;
    }
};