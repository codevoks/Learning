// Last updated: 6/7/2026, 11:24:57 PM
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