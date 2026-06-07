// Last updated: 6/7/2026, 11:26:43 PM
class Solution {
public:
    int f(int s,int e,int n,vector<int> &nums)
    {
        if(n==1)
        {
            return 0;
        }
        if(s>e)
        {
            return -1;
        }
        while(s<=e)
        {
            int mid= s + (e-s)/2;
            if(mid>0&&mid<n-1)
            {
                if(nums[mid]>nums[mid+1]&&nums[mid-1]<nums[mid])
                {
                    return mid;
                }
                else if(nums[mid-1]>nums[mid])
                {
                    e = mid-1;
                }
                else
                {
                    s =mid+1;
                }
            }
            else if(mid==0)
            {
                if(nums[0]>nums[1])
                {
                    return 0;
                }
                else
                {
                    return 1;
                }
            }
            else
            {
                if(nums[n-1]<nums[n-2])
                {
                    return n-2;
                }
                else
                {
                    return n-1;
                }
            }
        }
        return -1;
    }
    int findPeakElement(vector<int>& nums) 
    {
        int n = nums.size();
        return f(0,n-1,n,nums);
    }
};