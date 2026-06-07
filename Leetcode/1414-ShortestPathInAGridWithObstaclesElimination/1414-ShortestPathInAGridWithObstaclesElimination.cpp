// Last updated: 6/7/2026, 11:25:05 PM
class Solution {
public:
    #define mp make_pair
    using P=pair<int,pair<int,pair<int,int>>>;
    int dr[4]={-1,0,1,0};
    int dc[4]={0,1,0,-1};
    int m,n;
    int isValid(int r, int c,vector<vector<int>>& grid){
        return !(r<0 || r>=m || c<0 || c>=n);
    }
    void bfs(int sourceR, int sourceC, vector<vector<vector<int>>>& dist,vector<vector<int>>& grid, int k){
        dist[sourceR][sourceC][0]=0;
        queue<P> q;
        q.push(mp(dist[sourceR][sourceC][0],mp(0,mp(sourceR,sourceC))));
        while(!q.empty()){
            auto [d, state]=q.front();
            auto [obstaclesRemoved, originalNode]= state;
            int nodeR = originalNode.first;
            int nodeC = originalNode.second;
            q.pop();
            for(int i=0;i<4;i++){
                int neighR = nodeR+dr[i];
                int neighC = nodeC+dc[i];
                if(!isValid(neighR,neighC,grid) || obstaclesRemoved>k){
                    continue;
                }
                if(grid[neighR][neighC]==0){
                    if(dist[nodeR][nodeC][obstaclesRemoved]+1<dist[neighR][neighC][obstaclesRemoved]){
                        dist[neighR][neighC][obstaclesRemoved]=dist[nodeR][nodeC][obstaclesRemoved]+1;
                        q.push(mp(dist[neighR][neighC][obstaclesRemoved],mp(obstaclesRemoved,mp(neighR,neighC))));
                    }
                }else{
                    if(obstaclesRemoved<k && dist[nodeR][nodeC][obstaclesRemoved]+1<dist[neighR][neighC][obstaclesRemoved+1]){
                        dist[neighR][neighC][obstaclesRemoved+1]=dist[nodeR][nodeC][obstaclesRemoved]+1;
                        q.push(mp(dist[neighR][neighC][obstaclesRemoved+1],mp(obstaclesRemoved+1,mp(neighR,neighC))));
                    }
                }
            }
        }
    }
    void djikstra(int sourceR, int sourceC, vector<vector<vector<int>>>& dist,vector<vector<int>>& grid, int k){
        dist[sourceR][sourceC][0]=0;
        priority_queue<P,vector<P>,greater<P>> pq;
        pq.push(mp(dist[sourceR][sourceC][0],mp(0,mp(sourceR,sourceC))));
        while(!pq.empty()){
            auto [d, state]=pq.top();
            auto [obstaclesRemoved, originalNode]= state;
            int nodeR = originalNode.first;
            int nodeC = originalNode.second;
            pq.pop();
            for(int i=0;i<4;i++){
                int neighR = nodeR+dr[i];
                int neighC = nodeC+dc[i];
                if(!isValid(neighR,neighC,grid) || obstaclesRemoved>k){
                    continue;
                }
                if(grid[neighR][neighC]==0){
                    if(dist[nodeR][nodeC][obstaclesRemoved]+1<dist[neighR][neighC][obstaclesRemoved]){
                        dist[neighR][neighC][obstaclesRemoved]=dist[nodeR][nodeC][obstaclesRemoved]+1;
                        pq.push(mp(dist[neighR][neighC][obstaclesRemoved],mp(obstaclesRemoved,mp(neighR,neighC))));
                    }
                }else{
                    if(obstaclesRemoved<k && dist[nodeR][nodeC][obstaclesRemoved]+1<dist[neighR][neighC][obstaclesRemoved+1]){
                        dist[neighR][neighC][obstaclesRemoved+1]=dist[nodeR][nodeC][obstaclesRemoved]+1;
                        pq.push(mp(dist[neighR][neighC][obstaclesRemoved+1],mp(obstaclesRemoved+1,mp(neighR,neighC))));
                    }
                }
            }
        }
    }
    int shortestPath(vector<vector<int>>& grid, int k) {
        m=grid.size();
        n=grid[0].size();
        const int INF=1e9;
        vector<vector<vector<int>>> dist(m,vector<vector<int>>(n,vector<int>(k+1,INF)));
        //bfs(0,0,dist,grid,k);
        djikstra(0,0,dist,grid,k);
        int ans=INF;
        for(int i=0;i<=k;i++){
            cout<<dist[m-1][n-1][i]<<" ";
            ans=min(ans,dist[m-1][n-1][i]);
        }
        return ans>=INF?-1:ans;
    }
};