// Last updated: 6/7/2026, 11:27:42 PM
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int n = nums.size();
        int ans = nums[0];
        int sum= 0;
        for(int i = 0 ;i<n;i++)
        {
            sum = sum + nums[i];
            ans = max(ans,sum);
            sum = max(sum,0);
        }
        return ans;
    }
};