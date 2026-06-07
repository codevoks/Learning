// Last updated: 6/7/2026, 11:25:20 PM
class DSU {
public:
    unordered_map<char,char> parent;
    unordered_map<char, int> sizes;
    void makeSet(char a){
        if(parent.find(a)!=parent.end()){
            return;
        }
        parent[a]=a;
        sizes[a]=1;
    }

    char find(char a){
        if(parent[a]==a){
            return a;
        }
        return parent[a]=find(parent[a]);
    }

    void Union(char a, char b){
        char pa = find(a);
        char pb = find(b);
        if(pa==pb){
            return;
        }
        if(sizes[pa]<sizes[pb]){
            swap(pa,pb);
        }
        parent[pb]=pa;
        sizes[pa]+=sizes[pb];
    }
};

class Solution {
public:
    bool equationsPossible(vector<string>& equations) {
        DSU dsu;
        int n=equations.size();
        for(int i=0;i<n;i++){
            dsu.makeSet(equations[i][0]);
            dsu.makeSet(equations[i][3]);
        }
        for(int i=0;i<n;i++){
            if(equations[i][1]=='='){
                dsu.Union(equations[i][0],equations[i][3]);
            }
        }
        for(int i=0;i<n;i++){
            if(equations[i][1]=='!'){
                char pa = dsu.find(equations[i][0]);
                char pb = dsu.find(equations[i][3]);
                if(pa==pb){
                    return false;
                }
            }
        }
        return true;
    }
};