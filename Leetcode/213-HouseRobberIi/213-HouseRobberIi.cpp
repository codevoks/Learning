// Last updated: 6/10/2026, 9:47:05 PM
class Solution {
public:
    int robLinear(vector<int>& nums, int start, int end){
        int n=end-start+1;
        if(n==1){
            return nums[start];
        }
        if(n==2){
            return max(nums[start],nums[start+1]);
        }
        int prev2=nums[start];
        int prev1=max(nums[start],nums[start+1]);
        // 0,1,2,3,4,5
        // s,0,0,0,e,0 start!=0=0
        // 0,s,0,0,0,e start!=0=1
        for(int i=2;i<n;i++){
            int cur=max(prev2+nums[i+(start!=0)],prev1);
            prev2=prev1;
            prev1=cur;
        }
        return prev1;
    }
    int rob(vector<int>& nums) {
        //dp - here don't have any element as first so we don't have any element as ith also
        //dp state requires some identification but here we can't have it, and that's a problem
        //here we cannot take first and last house together, so we can make two cases - surely not taking first and surely not taking last
        //now the problem is standard Hourse Robber 1
        int n=nums.size();
        if(n==1){
            return nums[0];
        }
        return max(robLinear(nums,0,n-2),robLinear(nums,1,n-1));
    }
};