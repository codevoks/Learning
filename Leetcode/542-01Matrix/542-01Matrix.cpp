// Last updated: 6/7/2026, 11:25:58 PM
class Solution {
public:
    int m,n;

    int isValid(int r,int c){
        return !(r<0 || r>=m || c<0 || c>=n);
    }
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        int dr[4] = {-1,0,1,0};
        int dc[4] = {0,1,0,-1};
        m = mat.size();
        n = mat[0].size();
        vector<vector<int>> visited(m,vector<int> (n,0));
        vector<vector<int>> distance(m,vector<int> (n,0));
        queue<pair<int,int>> q;
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(!mat[i][j]){
                    visited[i][j]++;
                    q.push({i,j});
                }
            }
        }
        while(!q.empty()){
            auto [r,c] = q.front();
            q.pop();
            for(int i=0;i<4;i++){
                auto [nr,nc] = make_pair(r+dr[i],c+dc[i]);
                if(!isValid(nr,nc) || !mat[nr][nc] || visited[nr][nc]){
                    continue;   
                }
                distance[nr][nc]=distance[r][c]+1;
                visited[nr][nc]++;
                q.push({nr,nc});
            }
        }
        return distance;
    }
};