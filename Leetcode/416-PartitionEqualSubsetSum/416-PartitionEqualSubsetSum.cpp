// Last updated: 6/7/2026, 11:26:06 PM
class Solution {
public:
    bool f(int ind,int sum,vector<int> &nums,int size,vector<vector<int>> &dp)
    {
        if(sum==0)
        {
            return true;
        }
        if(ind==size-1)
        {
            return sum==nums[size-1];    
        }
        if(dp[ind][sum]!=-1)
        {
            return dp[ind][sum];
        }
        bool np=f(ind+1,sum,nums,size,dp);
        if(nums[ind]<=sum)
        {
            np=np||f(ind+1,sum-nums[ind],nums,size,dp);
        }
        return dp[ind][sum]=np;
    }
    bool canPartition(vector<int>& nums) {
        int sum = accumulate(nums.begin(),nums.end(),0);
        int size=nums.size();
        if(sum&1)
        {
            return false;
        }
        vector<vector<int>> dp(nums.size(),vector<int>(sum/2+1,-1));
        return f(0,sum/2,nums,size,dp);
    }
};