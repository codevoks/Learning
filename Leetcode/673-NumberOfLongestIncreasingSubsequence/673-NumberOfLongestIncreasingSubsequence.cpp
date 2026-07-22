// Last updated: 7/22/2026, 9:24:32 PM
class Solution {
public:
    int findNumberOfLIS(vector<int>& nums) {
        //dp - LIS ending at i
        //cnt - number of LIS ending at i
        int n=nums.size();
        vector<int> dp(n,1);
        vector<int> count(n,1);

        int lis=1;
        for(int i=0;i<n;i++){
            for(int j=0;j<i;j++){
                if(nums[j]<nums[i]){
                    if(dp[j]+1>dp[i]){
                        dp[i]=dp[j]+1;
                        count[i]=count[j];
                    }else if(dp[j]+1==dp[i]){
                        count[i]+=count[j];
                    }
                }
            }
            lis=max(lis,dp[i]);
        }
        int ans=0;
        for(int i=0;i<n;i++){
            if(dp[i]==lis){
                ans+=count[i];
            }
        }
        return ans;
    }
};