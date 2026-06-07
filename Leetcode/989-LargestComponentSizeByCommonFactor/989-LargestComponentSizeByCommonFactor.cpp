// Last updated: 6/7/2026, 11:25:23 PM
class DSU {
public:
    unordered_map<int,int> parent;
    unordered_map<int,int> sizes;
    void makeSet(int num){
        if(parent.find(num)!=parent.end()){
            return;
        }
        parent[num]=num;
        sizes[num]=1;
    }

    int find(int num){
        if(parent[num]==num){
            return num;
        }
        return parent[num]=find(parent[num]);
    }

    void Union(int a, int b){
        int pa = find(a);
        int pb = find(b);
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
    vector<int> getFactors(int num){
        vector<int> factors;
        for(int i=2; i*i<=num;i++){
            if(num%i==0){
                factors.push_back(i);
                if(num/i!=i){
                    factors.push_back(num/i);
                }
            }
        }
        return factors;
    }
    int largestComponentSize(vector<int>& nums) {
        DSU dsu;
        int n=nums.size();
        for(int i=0;i<n;i++){
            dsu.makeSet(nums[i]);
            vector<int> factors = getFactors(nums[i]);
            for(int j=0;j<factors.size();j++){
                dsu.makeSet(factors[j]);
                dsu.Union(nums[i],factors[j]);
            }
        }
        unordered_map<int,int> count;
        int ans=0;
        for(int i=0;i<n;i++){
            int leader = dsu.find(nums[i]);
            count[leader]++;
            ans=max(ans,count[leader]);
        }
        return ans;
    }
};