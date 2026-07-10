// Last updated: 7/10/2026, 10:50:43 PM
class Solution {
public:
    int uniquePaths(int m, int n) {
        //dp[i][j]=number of ways of reaching (i,j) from (0,0)
        //dp[i][j]=dp[i-1][j]+dp[i][j-1]
        //dp[0][0]=1
        vector<int> prev(n,0);
        prev[0]=1;
        for(int i=1;i<n;i++){
            prev[i]+=prev[i-1];
        }
        for(int i=1;i<m;i++){
            vector<int> cur(n);
            for(int j=0;j<n;j++){
                cur[j]=((j>=1)?cur[j-1]:0)+prev[j];
            }
            prev=cur;
        }
        return prev[n-1];
    }
};