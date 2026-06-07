// Last updated: 6/7/2026, 11:26:18 PM
class Solution {
public:
    int numSquares(int n) {
        //dp[i]=least number of perfect squares that sum up to i
        //dp[i]=min(1+dp[i-j])over all j(<i) such j is a perfect square
        vector<int> dp(n+1,1e9);
        dp[0]=0;
        dp[1]=1;
        for(int i=2;i<=n;i++){
            for(int j=1;j*j<=i;j++){
                dp[i]=min(dp[i],1+dp[i-j*j]);
            }
        }
        return dp[n];
    }
};