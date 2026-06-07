// Last updated: 6/7/2026, 11:26:27 PM
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int n = nums.size();
        vector<int> pre(n+1);
        for(int i =1;i<=n;i++)
        {
            pre[i]=pre[i-1]+nums[i-1];
        }
        int ans = 1e9;
        for(int i = 1;i<=n;i++)
        {
            auto it = lower_bound(pre.begin()+i,pre.end(),target+pre[i-1]);
            int c = it - (pre.begin()+i) + 1;
            if(it!=pre.end())
            {
                ans = min(ans,c);
            }
        }
        if(ans>=1e9)
        {
            return 0;
        }
        return ans;
    }
};