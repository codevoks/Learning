// Last updated: 6/7/2026, 11:24:54 PM
class Solution {
public:
    #define mp make_pair
    using P=pair<int,pair<int,int>>;
    void djikstra(int src, unordered_map<int,vector<pair<int,int>>>& adj, vector<int>& passingFees, vector<vector<int>>& dist,int maxTime){
        dist[src][0]=passingFees[src];
        priority_queue<P,vector<P>,greater<P>> pq;
        pq.push(mp(dist[src][0],mp(0,src)));
        while(!pq.empty()){
            auto [cost, node]=pq.top();
            auto [time, originalNode]=node;
            pq.pop();
            for(auto [neigh,w]:adj[originalNode]){
                if(time+w>maxTime){
                    continue;
                }
                if(dist[originalNode][time]+passingFees[neigh]<dist[neigh][time+w]){
                    dist[neigh][time+w]=dist[originalNode][time]+passingFees[neigh];
                    pq.push(mp(dist[neigh][time+w],mp(time+w,neigh)));
                }
            }
        }
    }
    int minCost(int maxTime, vector<vector<int>>& edges, vector<int>& passingFees) {
        const int INF=1e9;
        unordered_map<int,vector<pair<int,int>>> adj;
        int n=passingFees.size();
        for(int i=0;i<edges.size();i++){
            int u=edges[i][0];
            int v=edges[i][1];
            int w=edges[i][2];
            adj[u].push_back(mp(v,w));
            adj[v].push_back(mp(u,w));
        }
        vector<vector<int>> dist(n,vector<int>(maxTime+1,INF));
        djikstra(0,adj,passingFees,dist,maxTime);
        int ans=INF;
        for(int i=0;i<=maxTime;i++){
            ans=min(ans,dist[n-1][i]);
        }
        return ans==INF?-1:ans;
    }
};