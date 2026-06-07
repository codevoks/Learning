// Last updated: 6/7/2026, 11:25:49 PM
class DSU {
public:
    vector<int> parent, sz;
    DSU(int n){
        parent.resize(n+1);
        sz.resize(n+1,1);
        for(int i=0;i<=n;i++){
            parent[i]=i;
        }
    }

    int find(int node){
        if(parent[node]==node){
            return node;
        }
        return parent[node]=find(parent[node]);
    }

    void Union(int a, int b){
        int pa=find(a);
        int pb=find(b);
        if(pa==pb){
            return;
        }
        if(sz[pa]<sz[pb]){
            swap(pa,pb);
        }
        parent[pb]=parent[pa];
        sz[pa]+=sz[pb];
    }
};

class Solution {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int n=edges.size();
        DSU dsu(n);
        vector<int> ans;
        for(int i=0;i<n;i++){
            int u=edges[i][0];
            int v=edges[i][1];
            if(dsu.find(u)==dsu.find(v)){
                ans.push_back(u);
                ans.push_back(v);
                return ans;
            }else{
                dsu.Union(u,v);
            }
        }
        return ans;
    }
};