// Last updated: 6/7/2026, 11:25:19 PM
class Solution {
public:
    int m,n;
    int isValid(int r,int c){
        return !(r<0 || r>=m || c<0 || c>=n);
    }
    int orangesRotting(vector<vector<int>>& grid) {
        int dr[4]={-1,0,1,0};
        int dc[4]={0,-1,0,1};
        m = grid.size();
        n = grid[0].size();
        vector<vector<int>> visited(m,vector<int> (n,0));
        vector<vector<int>> time(m,vector<int> (n,0));
        queue<pair<int,int>> q;
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(grid[i][j]==2){
                    q.push({i,j});
                    visited[i][j]=1;
                }
            }
        }
        while(!q.empty()){
            auto [r,c] = q.front();
            q.pop();
            for(int i=0;i<4;i++){
                if(!isValid(r+dr[i],c+dc[i])||visited[r+dr[i]][c+dc[i]]||grid[r+dr[i]][c+dc[i]]!=1){
                    continue;
                }
                visited[r+dr[i]][c+dc[i]]=1;
                q.push({r+dr[i],c+dc[i]});
                time[r+dr[i]][c+dc[i]]=time[r][c]+1;
            }
        }
        int ans=0;
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(grid[i][j]==1&&!visited[i][j]){
                    return -1;
                }else if(grid[i][j]==1){
                    ans=max(ans,time[i][j]);
                }
            }
        }
        return ans;
    }
};