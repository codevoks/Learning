// Last updated: 9/13/2026, 9:02:13 AM
class Solution {
public:
    const int INF=1e9;
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        vector<vector<pair<int,int>>> adj(n+1,vector<pair<int,int>>());
        for(int i=0;i<times.size();i++){
            int u=times[i][0];
            int v=times[i][1];
            int w=times[i][2];
            adj[u].push_back(make_pair(v,w));
        }
        vector<int> distance(n+1,INF);
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
        distance[k]=0;
        pq.push(make_pair(0,k));
        int ans=0;
        while(!pq.empty()){
            auto [dist,node]=pq.top();
            pq.pop();
            for(auto [neigh,weight]:adj[node]){
                if(distance[node]+weight<distance[neigh]){
                    distance[neigh]=distance[node]+weight;
                    pq.push(make_pair(distance[neigh],neigh));
                }
            }
        }
        for(int i=1;i<=n;i++){
            ans=max(ans,distance[i]);
        }
        return ans>=INF?-1:ans;
    }
};