// Last updated: 6/7/2026, 11:24:42 PM
class Solution {
public:
    int returnToBoundaryCount(vector<int>& nums) {
        int sum = 0,ans=0;
        for(int i =0;i<nums.size();i++)
        {
            sum+=nums[i];
            if(sum==0)
            {
                ans++;
            }
        }
        return ans;
    }
};