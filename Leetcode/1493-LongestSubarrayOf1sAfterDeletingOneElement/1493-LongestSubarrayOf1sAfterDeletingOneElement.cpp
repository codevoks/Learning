// Last updated: 9/13/2026, 8:59:46 AM
class Solution {
public:
    int longestSubarray(vector<int>& nums) {
        int n = nums.size();
        int zeros=0;
        int i = 0,j = 0;
        int ans = 0;
        while(j<n){
            if(nums[j]==0){
                zeros++;
            }
            while(zeros>1){
                if(nums[i]==0){
                    zeros--;
                }
                i++;
            }
            ans=max(ans,j-i);
            j++;
        }
        return ans;
    }
};