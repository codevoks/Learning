// Last updated: 6/13/2026, 2:10:11 PM
class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {
        //dp[i]=number of ways to write i as different sum of sequences of nums[0...j]
        //dp[i]= sum of all dp[i-nums[j]] where j varies from 0 to nums.length();
        //dp[0]=1
        int n=nums.size();
        vector<unsigned int> dp(target+1);
        dp[0]=1;
        for(int i=1;i<=target;i++){
            dp[i]=0;
            for(int j=0;j<n;j++){
                if(i>=nums[j]){
                    dp[i]+=dp[i-nums[j]];
                }
            }
        }
        return dp[target];
    }
};


/*
    nums=[3], target=2
    dp[2]=dp[2-3]=dp[-1]=0
    nums=[2], target=2
    dp[2]=dp[2-2]=dp[0]=1
    nums=[1], target=2
    dp[2]=dp[2-1]=dp[1]=dp[1-1]=dp[0]=1

    nums = [1,2,3], target = 4
    dp[4]=sum(dp[4-1]+dp[4-2]+dp[4-3])=sum(dp[3]+dp[2]+dp[1])=sum(4+2+1)=7
    dp[3]=sum(dp[3-1]+dp[3-2]+dp[3-3])=sum(dp[2]+dp[1]+dp[0])=sum(2+1+1)=4
    dp[2]=sum(dp[2-1]+dp[2-2]+dp[2-3])=sum(dp[1]+dp[0]+dp[-1])=sum(1+1+0)=2
    dp[1]=sum(dp[1-1]+dp[1-2]+dp[1-3])=sum(dp[0]+dp[-1]+dp[-2])=sum(1+0+0)=1
    dp[0]=1
*/