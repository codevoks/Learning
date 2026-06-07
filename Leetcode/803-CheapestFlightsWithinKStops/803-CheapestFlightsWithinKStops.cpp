// Last updated: 6/7/2026, 11:25:36 PM
class Solution {
public:
    void djikstra(int src, int k, vector<vector<int>>& dist, vector<vector<pair<int,int>>>& adj){
        using P = pair<int,pair<int,int>>;
        dist[src][k]=0;
        priority_queue<P,vector<P>,greater<P>> pq;
        pq.push(make_pair(dist[src][k],make_pair(k,src)));
        while(!pq.empty()){
            auto [d,node]=pq.top();
            int stopsLeft = node.first;
            int originalNode = node.second;
            pq.pop();
            for(auto [neigh,w]:adj[originalNode]){
                if(stopsLeft<1){
                    continue;
                }
                int distance=w;
                if(dist[originalNode][stopsLeft]+distance<dist[neigh][stopsLeft-1]){
                    dist[neigh][stopsLeft-1]=dist[originalNode][stopsLeft]+distance;
                    pq.push(make_pair(dist[neigh][stopsLeft-1],make_pair(stopsLeft-1,neigh)));
                }
            }
        }
    }
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        int m=flights.size();
        vector<vector<pair<int,int>>> adj(n,vector<pair<int,int>>());
        for(int i=0;i<m;i++){
            int u=flights[i][0];
            int v=flights[i][1];
            int w=flights[i][2];
            adj[u].push_back(make_pair(v,w));
        }
        const int INF=1e9;
        //we are asuming that dst is also a stop, so we can tolerate at most k+1 stops
        vector<vector<int>> dist(n,vector<int>(k+2,INF));
        djikstra(src,k+1,dist,adj);
        int ans=INF;
        for(int i=0;i<=k+1;i++){
            ans=min(ans,dist[dst][i]);
        }
        return ans == INF ? -1 : ans;
    }
};