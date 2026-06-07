// Last updated: 6/7/2026, 11:26:30 PM
class Solution {
public:
    bool dfs(int node, vector<int>& color,vector<vector<int>>& adj){
        color[node]=1;
        for(auto neighbour: adj[node]){
            if(color[neighbour]==0){
                if(dfs(neighbour, color, adj)){
                    return true;
                }
            }else if(color[neighbour]==1){
                return true;
            }
        }
        color[node]=2;
        return false;
    }
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        int n=numCourses;
        vector<int> color(n);
        vector<vector<int>> adj(n,vector<int>());
        for(int i=0;i<prerequisites.size();i++){
            int v=prerequisites[i][0];
            int u=prerequisites[i][1];
            adj[u].push_back(v);
        }
        for(int i=0;i<n;i++){
            if(color[i]==0){
                if(dfs(i,color,adj)){
                    return false;
                }
            }
        }
        return true;
    }
};