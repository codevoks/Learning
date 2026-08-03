// Last updated: 8/3/2026, 9:54:19 PM
class Solution {
public:
    const int mod=1e9+7;
    int countVowelPermutation(int n) {
        //0->'a', 1->'e', 2->'i', 3->'o', 4->'u'
        //dp[i][j]=number of strings of length i with the rules and ending with j vowel
        //dp[i][0]=dp[i-1][1]+dp[i-1][2]+dp[i-1][4]
        //dp[i][1]=dp[i-1][0]+dp[i-1][2]
        //dp[i][2]=dp[i-1][1]+dp[i-1][3]
        //dp[i][3]=dp[i-1][2]
        //dp[i][4]=dp[i-1][2]+dp[i-1][3]
        vector<vector<long long int>> dp(n+1,vector<long long int>(5));
        for(int i=0;i<5;i++){
            dp[1][i]=1;
        }
        for(int i=2;i<=n;i++){
            dp[i][0]=((dp[i-1][1]+dp[i-1][2])%mod+dp[i-1][4])%mod;
            dp[i][1]=(dp[i-1][0]+dp[i-1][2])%mod;
            dp[i][2]=(dp[i-1][1]+dp[i-1][3])%mod;
            dp[i][3]=(dp[i-1][2])%mod;
            dp[i][4]=(dp[i-1][2]+dp[i-1][3])%mod;
        }
        long long int ans=0;
        for(int i=0;i<5;i++){
            ans+=(dp[n][i]%mod);
            ans%=mod;
        }
        return ans;
    }
};