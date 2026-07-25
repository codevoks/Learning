// Last updated: 7/25/2026, 10:28:09 PM
class Solution {
public:
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        //dp[i]=Length of LIS ending at index i
        sort(nums.begin(),nums.end());
        int n=nums.size();
        vector<int> dp(n,1),parent(n,-1);
        int maxLength=0,lastIndex=-1;
        for(int i=0;i<n;i++){
            for(int j=0;j<i;j++){
                if(nums[i]%nums[j]==0 && dp[j]+1>dp[i]){
                    parent[i]=j;
                    dp[i]=dp[j]+1;
                }
            }
            if(dp[i]>maxLength){
                maxLength=dp[i];
                lastIndex=i;
            }
        }
        vector<int> ans;
        while(lastIndex!=-1){
            ans.push_back(nums[lastIndex]);
            lastIndex=parent[lastIndex];
        }
        reverse(ans.begin(),ans.end());
        return ans;
    }
};