// Last updated: 8/15/2026, 5:37:45 PM
class Solution {
public:
    int shortestPathLength(vector<vector<int>>& graph) {
        //dp[mask][end]=shortes path visiting everything in mask and end at end, initial state of mask can be used to set starting city
        const int INF=1e9;
        int n=graph.size();
        int initialMask=0;
        int finalMask=(1<<n)-1;
        vector<vector<int>> distance(finalMask+1,vector<int>(n));
        queue<pair<int,int>> q;
        for(int i=0;i<n;i++){
            q.push(make_pair(initialMask|(1<<i),i));
        }
        while(!q.empty()){
            auto [mask,node]=q.front();
            q.pop();
            int dis=distance[mask][node];
            for(auto neigh: graph[node]){
                int newMask=mask|(1<<neigh);
                if(distance[newMask][neigh]){
                    continue;
                }
                distance[newMask][neigh]=distance[mask][node]+1;
                q.push(make_pair(newMask,neigh));
            }
        }
        int ans=INF;
        for(int i=0;i<n;i++){
            ans=min(ans,distance[finalMask][i]);
        }
        return ans;
    }
};