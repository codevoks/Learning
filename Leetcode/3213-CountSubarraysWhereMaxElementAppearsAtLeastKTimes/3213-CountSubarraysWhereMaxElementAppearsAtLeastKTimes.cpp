// Last updated: 6/7/2026, 11:24:47 PM
class Solution {
public:
    long long countSubarrays(vector<int>& nums, int k) 
    {
        int n = nums.size();
        int maxi = -1e9;
        for(int i =0;i<n;i++)
        {
            maxi=max(maxi,nums[i]);
        }
        vector<int> pre(n,0);
        pre[0]=nums[0]==maxi;
        for(int i =1;i<n;i++) 
        {
             pre[i]=pre[i-1]+(nums[i]==maxi);
        }
        long long ans =0;
        for(int i = 0;i<n;i++)
        {
            if(nums[i]==maxi)
            {
                int sum = pre[i];
                ans+=pre.end()-lower_bound(pre.begin()+i,pre.end(),k+sum-1);
            }
            else
            {
                int sum = pre[i];
                ans+=pre.end()-lower_bound(pre.begin()+i,pre.end(),k+sum);
            }
        }
        return ans;
    }
};