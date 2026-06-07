// Last updated: 6/7/2026, 11:26:37 PM
class Solution {
public:
    int rob(vector<int>& nums) {
        //dp[i]=maximum amount of money that can be looted, without looting adjacent houses
        //dp[i]=max(dp[i-1],nums[i]+dp[i-2])
        //dp[0]=nums[0]
        //dp[1]=max(nums[0],nums[1])
        int n=nums.size();
        if(n==1){
            return nums[0];
        }
        int prev2=nums[0];
        int prev1=max(prev2,nums[1]);
        int cur;
        for(int i=2;i<n;i++){
            cur=max(prev1,nums[i]+prev2);
            prev2=prev1;
            prev1=cur;
        }
        return prev1;
    }
};