// Last updated: 6/13/2026, 6:44:36 PM
class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& matrix) {
        //dp[i][j]=minimum sum of path for reaching (i,j) row from 0th row
        //dp[i][j]=matrix[i][j]+min(dp[i-1][j-1],dp[i-1][j],dp[i-1][j+1])
        //dp[0][j]=matrix[0][j]
        const int INF=1e9;
        int n=matrix.size();
        vector<int> prev(n,0);
        for(int i=0;i<n;i++){
            prev[i]=matrix[0][i];
        }
        for(int i=1;i<n;i++){
            vector<int> cur(n,0);
            for(int j=0;j<n;j++){
                int topLeft=(j-1>=0)?prev[j-1]:INF;
                int top=prev[j];
                int topRight=(j+1<n)?prev[j+1]:INF;
                cur[j]=matrix[i][j]+min(top,min(topLeft,topRight));
            }
            prev=cur;
        }
        int ans=INF;
        for(int i=0;i<n;i++){
            ans=min(ans,prev[i]);
        }
        return ans;
    }
};