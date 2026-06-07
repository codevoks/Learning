// Last updated: 6/7/2026, 11:25:35 PM
class Solution {
public:
    bool dfs(int node, vector<int>& state, vector<vector<int>>& graph){
        if(state[node]==1){
            return false;
        }
        if(state[node]==2){
            return true;
        }
        state[node]=1;
        for(auto neighbour: graph[node]){
            if(!dfs(neighbour, state, graph)){
                return false;
            }
        }
        state[node]=2;
        return true;
    }
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        int n=graph.size();
        vector<int> state(n);
        vector<int> ans;
        for(int i=0;i<n;i++){
            if(dfs(i,state,graph)){
                ans.push_back(i);
            }
        }
        return ans;
    }
};