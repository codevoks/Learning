// Last updated: 6/7/2026, 11:25:13 PM
class Solution {
public:
    int m,n;
    int isValid(int r,int c){
        return !(r<0 || r>=m || c<0 || c>=n);
    }
    int maxDistance(vector<vector<int>>& grid) {
        int dr[4]={-1,0,1,0};
        int dc[4]={0,1,0,-1};
        m = grid.size();
        n = grid[0].size();
        vector<vector<int>> visited (m,vector<int>(n,0));
        vector<vector<int>> distance (m,vector<int>(n,-1));
        queue<pair<int,int>> q;
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(grid[i][j]){
                    visited[i][j]=1;
                    distance[i][j]=0;
                    q.push({i,j});
                }
            }
        }
        int ans = -1;
        while(!q.empty()){
            auto [r,c] = q.front();
            q.pop();
            ans = grid[r][c]? ans:max(ans, distance[r][c]);
            for(int i=0;i<4;i++){
                auto [nr,nc] = make_pair(r+dr[i],c+dc[i]);
                if(!isValid(nr,nc) || grid[nr][nc] || visited[nr][nc]){
                    continue;
                }
                visited[nr][nc]=1;
                distance[nr][nc]=distance[r][c]+1;
                q.push({nr,nc});
            }
        }
        return ans;
    }
};