// Last updated: 6/7/2026, 11:27:02 PM
class Solution {
public:
    int longestConsecutive(vector<int>& nums) 
    {
        int n = nums.size();
        int ans = 0;
        unordered_map<int,int> chain;
        for(int i =0;i<n;i++)
        {
            chain[nums[i]]=1;
        }
        for(int i =0;i<n;i++)
        {
            int cur = 0;
            int val = nums[i];
            if(chain[val-1]==0)
            {
                while(chain[val])
                {
                    cur++;
                    val++;
                }
            }
            ans=max(ans,cur);
        }
        return ans;
    }
};