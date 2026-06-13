// Last updated: 6/13/2026, 11:14:01 AM
class Solution {
public:
    const int mod=1e9+7;
    int countGoodStrings(int low, int high, int zero, int one) {
        //dp[i]=number of good string that can be created of length i
        //dp[i]=if(i>=zero){dp[i]+=dp[i-zero]} if(i>=one){dp[i]+=dp[i-one]}
        //dp[0]=1
        //ans=sum of all dp's from dp[low] to dp[high]
        vector<int> dp(high+1);
        dp[0]=1;
        for(int i=1;i<=high;i++){
            dp[i]=0;
            if(i>=zero){
                dp[i]=(dp[i]+dp[i-zero])%mod;
            }
            if(i>=one){
                dp[i]=(dp[i]+dp[i-one])%mod;
            }
        }
        int ans=0;
        for(int i=low;i<=high;i++){
            ans=(ans+dp[i])%mod;
        }
        return ans;
    }
};