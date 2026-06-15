// Last updated: 6/15/2026, 4:26:26 PM
class Solution {
public:
    const int INF=1e9;
    int dp[50][50][50];
    int n;
    int getGain(int r1,int c1,int r2, vector<vector<int>>& grid){
        int c2=r1+c1-r2;
        if(c2<0||c2>=n){
            return -INF;
        }
        if(grid[r1][c1]==-1||grid[r2][c2]==-1){
            return -INF;
        }
        int gain=grid[r1][c1];
        if(r1!=r2||c1!=c2){
            gain+=grid[r2][c2];
        }
        return gain;
    }
    int validValue(int r1,int c1, int r2){
        int c2=r1+c1-r2;
        if(r1<0||r1>=n||c1<0||c1>=n||r2<0||r2>=n||c2<0||c2>=n){
            return -INF;
        }
        return dp[r1][c1][r2];
    }
    int cherryPickup(vector<vector<int>>& grid) {
        //
        //dp[r1][c1][r2][c2]=maximum cherries that can be picked when robot1 is on (r1,c1) and robot2 is on [r2][c2] and r1+c1=r2+c2 so we can actually reduce one dimension
        //gain=if(any of the grid is blocked){-INF}if(both robots are on different locations){2}if(both robots are on same location){1}
        //maxPrev=max(dp[r1-1][c1][r2-1],dp[r1-1][c1][r2],dp[r1][c1-1][r2-1],dp[r1][c1-1][r2])
        //dp[r1][c1][r2]=maxPrev+gain
        n=grid.size();
        dp[0][0][0]=getGain(0,0,0,grid);
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                for(int k=0;k<n;k++){
                    if(i==0&&j==0&&k==0){
                        continue;
                    }
                    int prevMax=max(max(validValue(i-1,j,k-1),validValue(i-1,j,k)),max(validValue(i,j-1,k-1),validValue(i,j-1,k)));
                    int gain=getGain(i,j,k,grid);
                    if(prevMax<=-INF||gain<=-INF){
                        dp[i][j][k]=-INF;
                    }else{
                        dp[i][j][k]=gain+prevMax;
                    }
                }
            }
        }
        return max(0,dp[n-1][n-1][n-1]);
    }
};