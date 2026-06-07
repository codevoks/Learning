// Last updated: 6/7/2026, 11:25:59 PM
class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        int n = nums.size();
        int ans =0;
        for(int i = 0;i<n;i++)
        {
            ans = ans ^ nums[i];
        }
        return ans;
    }
};