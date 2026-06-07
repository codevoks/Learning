// Last updated: 6/7/2026, 11:24:41 PM
class Solution {
public:
    int bin(int a,int b,int mod)
    {
        int ans = 1;
        while(b>0)
        {
            if(b%2)
            ans = (ans*a)%mod;
            a=(a*a)%mod;
            b/=2;
        }
        return ans;
    }
    vector<int> getGoodIndices(vector<vector<int>>& variables, int target) {
        int n = variables.size();
        vector<int> ans;
        for(int i = 0;i<n;i++)
        {
            int a = variables[i][0];
            int b = variables[i][1];
            int c = variables[i][2];
            int m = variables[i][3];
            int A = bin(a,b,10);
            int B = c;
            int M = m;
            int current = bin(A,B,M);
            cout<<" current = "<<current<<" at index i = "<<i<<"\n";
            if(current==target)
            {
                ans.push_back(i);
            }
        }
        return ans;
    }
};