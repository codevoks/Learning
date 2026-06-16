// Last updated: 6/16/2026, 4:04:44 PM
class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        //dp[i][j]=minimum cost to reach ith row starting from the (n-1)th row
        //dp[i][j]=min(dp[i+1][j],dp[i+1][j+1])
        //dp[n-1][j]=triangle[n-1][j]
        int n=triangle.size();
        vector<int> prev(n,0);
        for(int i=0;i<n;i++){
            prev[i]=triangle[n-1][i];
        }
        for(int i=n-2;i>=0;i--){
            vector<int> cur(n);
            for(int j=0;j<i+1;j++){
                cur[j]=triangle[i][j]+min(prev[j],prev[j+1]);
            }
            prev=cur;
        }
        return prev[0];
    }
};