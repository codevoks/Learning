// Last updated: 6/7/2026, 11:25:57 PM
class DSU {
public:
    vector<int> leader, sz;
    int components;
    DSU(int n){
        leader.resize(n+1);
        sz.resize(n+1);
        components=n;
        for(int i=0;i<=n;i++){
            leader[i]=i;
            sz[i]=1;
        }
    }

    int getLeader(int node){
        if(leader[node]==node){
            return node;
        }
        return leader[node]=getLeader(leader[node]);
    }

    void Union(int a, int b){
        int la = getLeader(a);
        int lb = getLeader(b);
        if(la==lb){
            return;
        }
        if(sz[la]<sz[lb]){
            swap(la,lb);
        }
        leader[lb]=leader[la];
        sz[la]+=sz[lb];
        components--;
    }
};

class Solution {
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        int n=isConnected.size();
        DSU obj(n);
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(isConnected[i][j]){
                    obj.Union(i,j);
                }
            }
        }
        return obj.components;
    }
};

