// Last updated: 8/15/2026, 5:38:25 PM
class Solution {
public:
    bool canIWin(int maxChoosableInteger, int desiredTotal) {
        if(desiredTotal<=0){
            return 1;
        }
        int n=maxChoosableInteger;
        int initialMask=0;
        int finalMask=(1<<n)-1;
        vector<int> maskToSum(finalMask+1);
        for(int mask=0;mask<=finalMask;mask++){
            int sum=0;
            for(int i=0;i<n;i++){
                if(!(mask&1<<i)){
                    continue;
                }
                sum+=(i+1);
            }
            maskToSum[mask]=sum;
        }
        if(finalMask<desiredTotal){
            return 0;
        }
        vector<int> dp(finalMask+1);
        dp[finalMask]=0;
        for(int mask=finalMask;mask>=initialMask;mask--){
            int currentSum=maskToSum[mask];
            if(currentSum>=desiredTotal){
                dp[mask]=0;
                continue;
            }
            for(int i=0;i<n;i++){
                if((mask&(1<<i))){
                    continue;
                }
                if(currentSum+(i+1)>=desiredTotal){
                    dp[mask]=1;
                }else{
                    int nextMask=mask|(1<<i);
                    dp[mask]|=(!dp[nextMask]);
                }
            }
        }
        return dp[0];
    }
};