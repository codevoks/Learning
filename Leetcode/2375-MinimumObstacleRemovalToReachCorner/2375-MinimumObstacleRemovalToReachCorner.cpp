// Last updated: 6/7/2026, 11:24:50 PM
class Solution {
public:
    int minimumObstacles(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> distance (m,vector<int> (n,1e9));
        int dr[4] = {-1,0,1,0};
        int dc[4] = {0,1,0,-1};
        deque<pair<int,int>> dq;
        dq.push_front({0,0});
        distance[0][0]=0;
        while(!dq.empty()){
            auto [r,c] = dq.front();
            dq.pop_front();
            for(int i=0;i<4;i++){
                int nr = r+dr[i];
                int nc = c+dc[i];
                if(nr<0 || nr>=m || nc<0 || nc>=n){
                    continue;
                }
                int weight = grid[nr][nc];
                int newDistance = distance[r][c] + weight;
                if(newDistance<distance[nr][nc]){
                    distance[nr][nc] = newDistance;
                    !grid[nr][nc]? dq.push_front({nr,nc}) : dq.push_back({nr,nc});
                }
            }
        }
        return distance[m-1][n-1];
    }
};