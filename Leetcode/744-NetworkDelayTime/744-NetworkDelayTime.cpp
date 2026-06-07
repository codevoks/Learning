// Last updated: 6/7/2026, 11:25:42 PM
class Solution {
public:
    using P=pair<int,int>;
    void djikstra(int source, vector<vector<pair<int,int>>>& adj, vector<int>& dist){
        priority_queue<P,vector<P>,greater<P>> pq;
        pq.push(make_pair(0,source));
        while(!pq.empty()){
            auto [d,node] = pq.top();
            pq.pop();
            for(auto [neigh,wt]: adj[node]){
                if(dist[node]+wt<dist[neigh]){
                    dist[neigh]=dist[node]+wt;
                    pq.push(make_pair(dist[neigh],neigh));
                }
            }
        }
    }
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        vector<vector<pair<int,int>>> adj(n+1,vector<pair<int,int>>());
        for(int i=0;i<times.size();i++){
            int u=times[i][0];
            int v=times[i][1];
            int w=times[i][2];
            adj[u].push_back(make_pair(v,w));
        }
        vector<int> dist(n+1, 1e9);
        dist[k]=0;
        djikstra(k,adj,dist);
        int ans=0;
        for(int i=1;i<=n;i++){
            ans=max(ans,dist[i]);
        }
        if(ans>=1e9){
            ans=-1;
        }
        return ans;
    }
};