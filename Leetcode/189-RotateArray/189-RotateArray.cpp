// Last updated: 6/7/2026, 11:26:38 PM
class Solution {
public:
    void rotate(vector<int>& nums, int k) 
    {
        int n = nums.size();
        k%=n;
        vector<int> a;
        for(int i = n-k;i<n;i++)
        {
            if(i>=0)
            a.push_back(nums[i]);
        }
        for(int i = n-1;i>=0;i--)
        {
            if(i-k>=0)
            nums[i]=nums[i-k];
        }
        for(int i=0;i<min(n,k);i++)
        {
            nums[i]=a[i];
        }
        return;
    }
};