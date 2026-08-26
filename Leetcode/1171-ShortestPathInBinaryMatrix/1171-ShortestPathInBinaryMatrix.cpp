// Last updated: 8/26/2026, 4:49:10 PM
class Solution {
public:
    int dr[8]={-1,-1,0,1,1,1,0,-1};
    int dc[8]={0,1,1,1,0,-1,-1,-1};
    int n=0;
    int isValid(int row,int column){
        return !(row<0||row>=n||column<0||column>=n);
    }
    void bfs(int r,int c,vector<vector<int>>& distance,vector<vector<int>>& grid){
        queue<pair<int,int>> q;
        q.push(make_pair(r,c));
        distance[r][c]=1;
        while(!q.empty()){
            auto [row,column]=q.front();
            q.pop();
            for(int i=0;i<8;i++){
                int nr=row+dr[i];
                int nc=column+dc[i];
                if(!isValid(nr,nc)||grid[nr][nc]){
                    continue;
                }
                if(distance[nr][nc]!=-1){
                    continue;
                }
                distance[nr][nc]=1+distance[row][column];
                q.push(make_pair(nr,nc));
            }
        }
    }
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        n=grid.size();
        vector<vector<int>> distance(n,vector<int>(n,-1));
        if(grid[0][0]==1||grid[n-1][n-1]==1){
            return -1;
        }
        bfs(0,0,distance,grid);
        return distance[n-1][n-1];
    }
};