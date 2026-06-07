// Last updated: 6/7/2026, 11:25:41 PM
class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        //dp[i] = minimum cost to reach i index from 0 or 1
        //dp[i] = min(cost[i-1]+dp[i-1],cost[i-2]+dp[i-2])
        //dp[0] = 0
        //dp[1] = 0
        int n=cost.size();
        vector<int> dp(n+1);
        dp[0]=0;
        dp[1]=0;
        for(int i=2;i<=n;i++){
            dp[i]=min(cost[i-1]+dp[i-1],cost[i-2]+dp[i-2]);
        }
        return dp[n];
    }
};