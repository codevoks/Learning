// Last updated: 9/13/2026, 8:58:46 AM
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