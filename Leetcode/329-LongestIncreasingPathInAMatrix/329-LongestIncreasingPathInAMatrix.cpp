// Last updated: 6/7/2026, 11:26:13 PM
class Solution {
public:
    int f(int i, int j,vector<vector<int>> &A,vector<vector<int>> &dp)
{
    if(i<0||i>=A.size()||j<0||j>=A[0].size())
    {
        return 0;
    }
    if(dp[i][j]>0)
    {
        return dp[i][j];
    }
    int c = 1;
    //right
    if(j+1>=0&&j+1<A[0].size()&&A[i][j+1]>A[i][j])
    {
        c=max(c,1+f(i,j+1,A,dp));
    }
    //left
    if(j-1>=0&&j-1<A[0].size()&&A[i][j-1]>A[i][j])
    {
        c=max(c,1+f(i,j-1,A,dp));
    }
    //down
    if(i+1>=0&&i+1<A.size()&&A[i+1][j]>A[i][j])
    {
        c=max(c,1+f(i+1,j,A,dp));
    }
    //up
    if(i-1>=0&&i-1<A.size()&&A[i-1][j]>A[i][j])
    {
        c=max(c,1+f(i-1,j,A,dp));
    }
    return dp[i][j]=c;
}
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        vector<vector<int>> A=matrix;
        int r = A.size();
    int c = A[0].size();
    vector<vector<int>> dp(r,vector<int>(c,0));
    int ans = 0;
    for(int i = 0;i<r;i++)
    {
        for(int j = 0;j<c;j++)
        {
            ans = max(ans,f(i,j,A,dp));
        }
    }
    return ans;
        
    }
};