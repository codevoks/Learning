// Last updated: 6/7/2026, 11:26:35 PM
class Solution {
public:
    const int di[4]={-1,0,1,0},dj[4]={0,-1,0,1};
    int n,m;

    int isValid(int i, int j){
        return (0<=i&&i<n&&0<=j&&j<m);
    }

    void bfs(int startX, int startY, vector<vector<char>> &grid, vector<vector<int>> &visited){
        queue<pair<int,int>> q;
        q.push({startX,startY});
        visited[startX][startY]=1;
        while(!q.empty()){
            auto node = q.front();
            q.pop();
            for(int i = 0;i<4;i++){
                int ni = node.first+di[i], nj = node.second+dj[i];
                if(isValid(ni,nj)&&grid[ni][nj]=='1'&&!visited[ni][nj]){
                    q.push({ni,nj});
                    visited[ni][nj]=1;
                }
            }
        }
    }

    int numIslands(vector<vector<char>>& grid) {
        n = grid.size();
        m = grid[0].size();
        int ans = 0;
        vector<vector<int>> visited (n,vector<int> (m,0));
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(grid[i][j]=='1'&&!visited[i][j]){
                    bfs(i,j,grid,visited);
                    ans++;
                }
            }
        }
        return ans;
    }
};