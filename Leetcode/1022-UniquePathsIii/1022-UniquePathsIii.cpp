// Last updated: 8/8/2026, 5:22:31 PM
class Solution {
public:
    int m=0,n=0;
    int isValid(int r,int c){
        return !(r<0||r>=m||c<0||c>=n);
    }
    int dr[4]={-1,0,1,0};
    int dc[4]={0,1,0,-1};
    int uniquePathsIII(vector<vector<int>>& grid) {
        m=grid.size();
        n=grid[0].size();
        int k=0;
        int initialCell=0,finalCell=0;
        vector<vector<int>> id(m,vector<int>(n,-1));
        vector<pair<int,int>> pos;
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(grid[i][j]==-1){
                    continue;
                }
                if(grid[i][j]==1){
                    initialCell=k;
                }else if(grid[i][j]==2){
                    finalCell=k;
                }
                id[i][j]=k;
                pos.push_back(make_pair(i,j));
                k++;
            }
        }
        //dp[mask][node]=number of paths to get from starting state to this state
        int initialMask=(1<<initialCell);
        int finalMask=(1<<k)-1;
        vector<vector<int>> dp(finalMask+1,vector<int>(k));
        dp[initialMask][initialCell]=1;
        for(int mask=initialMask;mask<=finalMask;mask++){
            //any mask should contain initialCell
            if(!(mask&(1<<initialCell))){
                continue;
            }
            for(int current=0;current<k;current++){
                //current cell cannot be initial cell
                if(current==initialCell){
                    continue;
                }
                //current cell must be present in current mask
                if(!(mask&(1<<current))){
                    continue;
                }
                //don't visit finalCell until its the last
                if(current==finalCell && mask!=finalMask){
                    continue;
                }
                int previousMask=mask&~(1<<current);
                auto [r,c]=pos[current];
                for(int i=0;i<4;i++){
                    int pr=r+dr[i];
                    int pc=c+dc[i];
                    if(!isValid(pr,pc)||grid[pr][pc]==-1){
                        continue;
                    }
                    dp[mask][current]+=dp[previousMask][id[pr][pc]];
                }
            }
        }
        return dp[finalMask][finalCell];
    }
};