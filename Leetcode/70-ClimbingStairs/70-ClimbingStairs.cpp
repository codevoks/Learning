// Last updated: 6/7/2026, 11:27:37 PM
class Solution {
public:
    int climbStairs(int n) {
        //dp[i] = number of ways to reach i from 0
        //dp[i] = dp[i-1]+dp[i-2]
        //dp[0]=1
        //dp[1]=1
        vector<int> dp(n+1,-1);
        dp[0]=1;
        dp[1]=1;
        for(int i=2;i<=n;i++){
            dp[i]=dp[i-1]+dp[i-2];
        }
        return dp[n];
    }
};