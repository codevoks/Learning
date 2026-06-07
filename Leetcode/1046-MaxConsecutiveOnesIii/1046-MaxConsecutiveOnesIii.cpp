// Last updated: 6/7/2026, 11:25:17 PM
class Solution {
public:
    int longestOnes(vector<int>& nums, int k) {
        int n = nums.size();
        int ans = 0;
        int i=0,j=0;
        while(j<n){
            if(nums[j]==0){
                k--;
            }
            while(k<0){
                if(nums[i]==0){
                    k++;
                }
                i++;
            }
            ans = max(ans,j-i+1);
            j++;
        }
        return ans;
    }
};