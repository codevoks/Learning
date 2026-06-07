// Last updated: 6/7/2026, 11:25:51 PM
class Solution {
public:
    int f(int ind,int pre,vector<vector<int>> &A,vector<vector<int>> &dp)
{
    if(ind==A.size())
    {
        return 0;
    }
    if(dp[ind][pre+1]!=-1)
    {
        return dp[ind][pre+1];
    }
    int np = f(ind+1,pre,A,dp);
    //int p = INT_MIN;
    if(pre+1==0||A[pre][1]<A[ind][0])
    {
        np = max(np,1+f(ind+1,ind,A,dp)); 
    }
    return dp[ind][pre+1]=np;
}
    int findLongestChain(vector<vector<int>>& pairs) {
        int n =pairs.size();
    vector<vector<int>> dp(n,vector<int> (n+1,-1));
    sort(pairs.begin(),pairs.end());
    return f(0,-1,pairs,dp);
        
    }
};