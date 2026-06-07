// Last updated: 6/7/2026, 11:25:25 PM
class DSU {
public:
    unordered_map<int,int> parent;
    unordered_map<int,int> sizes;
    int components;

    DSU(int n){
        components=n;
    }

    void makeSet(int node){
        if(parent.find(node)!=parent.end()){
            return;
        }
        parent[node]=node;
        sizes[node]=1;
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
        if(sizes[pa]<sizes[pb]){
            swap(pa,pb);
        }
        parent[pb]=pa;
        sizes[pa]+=sizes[pb];
        components--;
    }

};

class Solution {
public:
    int removeStones(vector<vector<int>>& stones) {
        int n=stones.size();
        DSU dsu(n);
        for(int i=0;i<n;i++){
            dsu.makeSet(i);
        }
        for(int i=0;i<n;i++){
            pair<int,int> node = make_pair(stones[i][0],stones[i][1]);
            for(int j=0;j<n;j++){
                pair<int,int> currentNode = make_pair(stones[j][0],stones[j][1]);
                if(node==currentNode){
                    continue;
                }else if(node.first==currentNode.first || node.second==currentNode.second){
                    dsu.Union(i,j);
                }
            }
        }
        return n-dsu.components;
    }
};