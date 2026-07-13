// Last updated: 7/13/2026, 8:23:06 PM
class Solution {
public:
    int n=0;
    int isInvalid(int sum,int goal){
        return sum>goal;
    }
    int atMostGoal(vector<int>& nums, int goal){
        if(goal<0){
            return 0;
        }
        int l=0;
        int sum=0;
        int ans=0;

        for(int r=0;r<n;r++){
            sum+=nums[r];

            while(isInvalid(sum,goal)){
                sum-=nums[l];
                l++;
            }

            ans+=(r-l+1);
        }
        return ans;
    }
    int numSubarraysWithSum(vector<int>& nums, int goal) {
        n=nums.size();
        return atMostGoal(nums,goal)-atMostGoal(nums,goal-1);
    }
};