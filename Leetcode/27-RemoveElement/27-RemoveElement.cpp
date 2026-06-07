// Last updated: 6/7/2026, 11:27:51 PM
class Solution {
public:
#define INF 1e9
    int removeElement(vector<int>& nums, int val) {
        int n =nums.size();
        int ind = 0;
        for(int i = 0;i<n;i++)
        {
            if(val!=nums[i])
            {
                nums[ind]=nums[i];
                ind++;
            }
        }
        return ind;
    }
};