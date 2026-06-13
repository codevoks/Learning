// Last updated: 6/13/2026, 6:45:14 PM
class Solution {
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        //dp[i][j]=minimum initial health to reach (m-1,n-1) from (i,j)
        //minimum health to reach next = min(dp[i+1][j],dp[i][j+1]);
        //dp[i][j]= if(minimumNext<=dungeon[i][j]){we gain more than enough so take 1}else remove/add extra dp[i][j]=minimumNext-dungeon[i][j]
        //dp[m-1][n-1]=(dungeon[m-1][n-1]<=0)?(1+abs(dungeon[m-1][n-1]):1)
        const int INF=1e9;
        int m=dungeon.size();
        int n=dungeon[0].size();
        vector<vector<int>> dp(m,vector<int>(n,0));
        dp[m-1][n-1]=1;
        if(dungeon[m-1][n-1]<=0){
            dp[m-1][n-1]+=abs(dungeon[m-1][n-1]);
        }
        for(int i=m-1;i>=0;i--){
            for(int j=n-1;j>=0;j--){
                if(i==m-1&&j==n-1){
                    continue;
                }
                int right=(j+1<n)?dp[i][j+1]:INF;
                int down=(i+1<m)?dp[i+1][j]:INF;
                int minNext=min(right,down);
                if(minNext<=dungeon[i][j]){
                    dp[i][j]=1;
                }else{
                    dp[i][j]=minNext-dungeon[i][j];
                }
            }
        }
        return dp[0][0];
    }
};