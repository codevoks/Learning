// Last updated: 7/18/2026, 12:29:33 PM
class Solution {
public:
    int countPairs(vector<int>& nums, int target) {
        int n=nums.size();
        int l=0,r=n-1;
        int ans=0;
        sort(nums.begin(),nums.end());
        while(l<r){
            if(nums[l]+nums[r]>=target){
                //if nums[l]+nums[r]>=target then nums[x]+nums[r]>=target for all x>=l so eliminate r
                r--; 
            }else{
                //if nums[l]+nums[r]<target then nums[l]+nums[x]<target for all x<=r so take contribution of entire window
                ans+=(r-l);
                //now since we have all the contribution of [l,x] x<=r we can elminate l
                l++;
            }
        }
        return ans;
    }
};