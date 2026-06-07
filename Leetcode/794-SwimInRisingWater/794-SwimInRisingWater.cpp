// Last updated: 6/7/2026, 11:25:37 PM
class Solution {
public:
    int dr[4]={-1,0,1,0};
    int dc[4]={0,1,0,-1};
    int n;
    int isValid(int r,int c){
        return !(r<0||r>=n||c<0||c>=n);
    }
    void djikstra(int sourceR,int sourceC, vector<vector<int>>& dist, vector<vector<int>>& grid){
        using P=pair<int,pair<int,int>>;
        priority_queue<P,vector<P>,greater<P>> pq;
        dist[0][0]=grid[0][0];
        pq.push(make_pair(dist[0][0],make_pair(sourceR,sourceC)));
        while(!pq.empty()){
            auto [d,node]=pq.top();
            pq.pop();
            int r=node.first;
            int c=node.second;
            for(int i=0;i<4;i++){
                int nr=r+dr[i];
                int nc=c+dc[i];
                if(!isValid(nr,nc)){
                    continue;
                }
                int distance=max(dist[r][c],grid[nr][nc]);
                if(distance<dist[nr][nc]){
                    dist[nr][nc]=distance;
                    pq.push(make_pair(dist[nr][nc],make_pair(nr,nc)));
                }
            }
        }
    }
    int swimInWater(vector<vector<int>>& grid) {
        n=grid.size();
        const int INF=1e9;
        vector<vector<int>> dist(n,vector<int>(n,INF));
        djikstra(0,0,dist,grid);
        return dist[n-1][n-1];
    }
};