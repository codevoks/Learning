// Last updated: 6/7/2026, 11:26:26 PM
class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        map<int,pair<int,int>> mp;
        int n = nums.size();
        for(int i = 0;i<n;i++)
        {
            if(mp[nums[i]].first!=0&&i-mp[nums[i]].second<=k)
            {
                return 1;
            }
            mp[nums[i]].first++;
            mp[nums[i]].second=i;
        }
        return 0;
    }
};