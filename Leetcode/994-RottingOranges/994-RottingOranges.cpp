// Last updated: 9/13/2026, 9:00:56 AM
class Solution {
public:
    int dr[4]={-1,0,1,0};
    int dc[4]={0,1,0,-1};
    int m=0,n=0;
    int isValid(int r, int c){
        return !(r<0||r>=m||c<0||c>=n);
    }
    int orangesRotting(vector<vector<int>>& grid) {
        m=grid.size();
        n=grid[0].size();
        const int INF=1e9;
        vector<vector<int>> distance(m,vector<int>(n,INF));
        queue<pair<int,int>> q;
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(grid[i][j]==2){
                    q.push(make_pair(i,j));
                    distance[i][j]=0;
                }
            }
        }
        while(!q.empty()){
            auto [r,c]=q.front();
            q.pop();
            for(int i=0;i<4;i++){
                int nr=r+dr[i];
                int nc=c+dc[i];
                if(!isValid(nr,nc)||grid[nr][nc]!=1){
                    continue;
                }
                if(distance[r][c]+1<distance[nr][nc]){
                    distance[nr][nc]=1+distance[r][c];
                    q.push(make_pair(nr,nc));
                }
            }
        }
        int ans=0;
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(grid[i][j]==1){
                    ans=max(ans,distance[i][j]);
                }
            }
        }
        return ans>=INF?-1:ans;
    }
};