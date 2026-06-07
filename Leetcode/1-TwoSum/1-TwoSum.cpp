// Last updated: 6/7/2026, 11:28:06 PM
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int n = nums.size();
        map<int,int> mp;
        for(int i=0;i<n;i++)
        {
            mp[nums[i]]=i;
        }
        for(int i = 0;i<n;i++)
        {
            int s = target - nums[i];
            if(mp[s]>0&&mp[s]!=i)
            {
                return {i,mp[s]};
            }
        }
        return {};
    }
};