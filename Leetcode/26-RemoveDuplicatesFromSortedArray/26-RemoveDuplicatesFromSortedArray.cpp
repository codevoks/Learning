// Last updated: 6/7/2026, 11:27:52 PM
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int n = nums.size();
        //first element is always unique
        int cur = 1;
        for(int i=1;i<n;i++)
        {
            //if nums[i]!=nums[i-1] then we have found ourselves a new unique element
            if(nums[i]!=nums[i-1])
            {
                //place it on the current index
                nums[cur]=nums[i];
                cur++;
            }
        }
        return cur;
    }
};