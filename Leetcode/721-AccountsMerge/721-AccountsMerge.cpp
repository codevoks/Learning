// Last updated: 6/7/2026, 11:25:47 PM
class DSU {
public:
    unordered_map<string, string> parent;
    unordered_map<string, int> size;
    void makeSet(string email){
        if(parent.find(email)!=parent.end()){
            return;
        }
        parent[email]=email;
        size[email]=1;
    }

    string find(string email){
        if(parent[email]==email){
            return email;
        }
        return parent[email]=find(parent[email]);
    }

    void Union(string a, string b){
        string pa = find(a);
        string pb = find(b);
        if(pa==pb){
            return;
        }
        if(size[pa]<size[pb]){
            swap(pa,pb);
        }
        parent[pb]=pa;
        size[pa]+=size[pb];
    }
};

class Solution {
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        DSU dsu;
        unordered_map<string, string> emailToName;
        int n=accounts.size();
        for(int i=0;i<n;i++){
            string name=accounts[i][0];
            for(int j=1;j<accounts[i].size();j++){
                emailToName[accounts[i][j]]=name;
                dsu.makeSet(accounts[i][j]);
            }
            for(int j=2;j<accounts[i].size();j++){
                dsu.Union(accounts[i][1],accounts[i][j]);
            }
        }

        unordered_map<string,vector<string>> groups;
        for(auto it: dsu.parent){
            string email = it.first;
            string leader = dsu.find(email);
            groups[leader].push_back(email);
        }

        vector<vector<string>> ans;
        for(auto it: groups){
            vector<string> entry;
            string leader = it.first;
            vector<string> emails = it.second;
            sort(emails.begin(),emails.end());
            entry.push_back(emailToName[leader]);
            for(int i=0;i<emails.size();i++){
                entry.push_back(emails[i]);
            }
            ans.push_back(entry);
        }
        return ans;
    }
};