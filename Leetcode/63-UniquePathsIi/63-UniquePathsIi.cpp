// Last updated: 7/10/2026, 10:50:50 PM
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        //dp[i][j]=number of ways to reach (i,j) from (0,0)
        //dp[i][j]=if(up is not blocked){dp[i][j]+=dp[i-1][j]} if(left is not blocked){dp[i][j]+=dp[i][j-1]}
        //dp[i][j]=1 if no obstable, 0 otherwise
        int m=obstacleGrid.size();
        int n=obstacleGrid[0].size();
        vector<int> prev(n,0);
        prev[0]=!obstacleGrid[0][0];
        for(int i=1;i<n;i++){
            prev[i]=(obstacleGrid[0][i]?0:(prev[i]+prev[i-1]));
        }
        for(int i=1;i<m;i++){
            vector<int> cur(n);
            for(int j=0;j<n;j++){
                if(obstacleGrid[i][j]){
                    cur[j]=0;
                }else{
                    cur[j]=((j>0)?cur[j-1]:0)+prev[j];
                }
            }
            prev=cur;
        }
        return prev[n-1];
    }
};