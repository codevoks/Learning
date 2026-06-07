// Last updated: 6/7/2026, 11:25:01 PM
class Solution {
public:
    int m,n;
    int isValidPosition(int nr,int nc){
        return !(nr<0 || nr>=m || nc<0 || nc>=n);
    }

    unordered_map<int,pair<int,int>> gridMove = {
            {1,{0,1}},{2,{0,-1}},{3,{1,0}},{4,{-1,0}}
        };

    int minCost(vector<vector<int>>& grid) {
        int dr[4]={0,1,0,-1};
        int dc[4]={1,0,-1,0};
        m = grid.size();
        n = grid[0].size();
        vector<vector<int>> distance(m,vector<int> (n,1e9));
        deque<pair<int,int>> dq;
        distance[0][0]=0;
        dq.push_front({0,0});
        while(!dq.empty()){
            auto [r,c] = dq.front();
            dq.pop_front();
            for(int i=0;i<4;i++){
                int cost = gridMove.at(grid[r][c])!=make_pair(dr[i],dc[i]);
                if(isValidPosition(r+dr[i],c+dc[i]) && distance[r][c]+cost<distance[r+dr[i]][c+dc[i]]){
                    distance[r+dr[i]][c+dc[i]]=distance[r][c]+cost;
                    if(cost){
                        dq.push_back({r+dr[i],c+dc[i]});
                    }else{
                        dq.push_front({r+dr[i],c+dc[i]});
                    }
                }
            }
        }
        return distance[m-1][n-1];
    }
};