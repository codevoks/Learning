// Last updated: 9/13/2026, 8:59:15 AM
class Solution {
public:
    const int INF=1e9;
    int dr[4]={-1,0,1,0};
    int dc[4]={0,1,0,-1};
    int m=0,n=0;
    int isValid(int r,int c){
        return !(r<0||r>=m||c<0||c>=n);
    }
    int minimumObstacles(vector<vector<int>>& grid) {
        m=grid.size();
        n=grid[0].size();
        vector<vector<int>> distance(m,vector<int>(n,INF));
        deque<pair<int,int>> dq;
        dq.push_front(make_pair(0,0));
        distance[0][0]=0;
        while(!dq.empty()){
            auto [r,c]=dq.front();
            dq.pop_front();
            for(int i=0;i<4;i++){
                int nr=r+dr[i];
                int nc=c+dc[i];
                if(!isValid(nr,nc)){
                    continue;
                }
                if(distance[nr][nc]>=INF){
                    if(grid[nr][nc]==1){
                        if(distance[r][c]<1+distance[nr][nc]){
                            distance[nr][nc]=1+distance[r][c];
                            dq.push_back(make_pair(nr,nc));
                        }
                    }else{
                        if(distance[r][c]<distance[nr][nc]){
                            distance[nr][nc]=distance[r][c];
                            dq.push_front(make_pair(nr,nc));
                        }
                    }
                }
            }
        }
        return distance[m-1][n-1];
    }
};