#include<bits/stdc++.h>
using namespace std;
using lli = long long;
#define INF 1e9
const int mod=1e9+7;

void djikstra(int src, int l, vector<vector<pair<int,int>>>& adj, vector<vector<int>>& dist){
    priority_queue<pair<int,pair<int,int>>,vector<pair<int,pair<int,int>>>,greater<pair<int,pair<int,int>>>> pq;
    dist[src][l]=0;
    pq.push(make_pair(dist[src][l],make_pair(l,src)));
    while(!pq.empty()){
        auto [d,state]=pq.top();
        auto [fuel,originalNode]=state;
        pq.pop();
        for(auto [neigh,w]:adj[originalNode]){
            if(l<w){
                continue;
            }
            if(fuel>=w){
                if(dist[originalNode][fuel]+0<dist[neigh][fuel-w]){
                    dist[neigh][fuel-w]=dist[originalNode][fuel]+0;
                    pq.push(make_pair(dist[neigh][fuel-w],make_pair(fuel-w,neigh)));
                }
            }
        }
        if(dist[originalNode][fuel]+1<dist[originalNode][l]){
            dist[originalNode][l]=dist[originalNode][fuel]+1;
            pq.push(make_pair(dist[originalNode][l],make_pair(l,originalNode)));
        }
    }
}

void solve(){
    int n,m,l;
    cin>>n>>m>>l;
    vector<vector<pair<int,int>>> adj(n+1,vector<pair<int,int>>());
    for(int i=0;i<m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        adj[u].push_back(make_pair(v,w));
        adj[v].push_back(make_pair(u,w));
    }
    int q;
    cin>>q;
    for(int i=0;i<q;i++){
        vector<vector<int>> dist(n+1,vector<int>(l+1,INF));
        int s,t;
        cin>>s>>t;
        djikstra(s,l,adj,dist);
        int ans=INF;
        for(int i=0;i<=l;i++){
            ans=min(ans,dist[t][i]);
        }
        cout<<(ans>=INF?-1:ans)<<"\n";
    }
}

signed int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int _t=1;
    //cin>>_t;
    while(_t--){
        solve();
    }
}

