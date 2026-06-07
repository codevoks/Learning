// Last updated: 6/7/2026, 11:27:11 PM
class Solution {
public:
    int f(int i,int j,string s,string t,vector<vector<int>> &dp)
    {
        if(j==0)
        {
            return 1;
        }
        if(i==0)
        {
            return 0;
        }
        if(dp[i][j]!=-1)
        {
            return dp[i][j];
        }
        int ans = 0;
        if(s[i-1]==t[j-1])
        {
            ans =  f(i-1,j-1,s,t,dp)+f(i-1,j,s,t,dp);
        }
        else
        {
            ans =  f(i-1,j,s,t,dp);
        }
        return dp[i][j]=ans;
    }
    int numDistinct(string s, string t) {
        int n = s.length();
        int m = t.length();
        vector<vector<double>> dp(n+1,vector<double>(m+1,0));
        for(int i = 0;i<=n;i++)
        {
            dp[i][0]=1;
        }
        for(int j = 1;j<=m;j++)
        {
            dp[0][j]=0;
        }
        for(int i = 1;i<=n;i++)
        {
            for(int j = 1;j<=m;j++)
            {
                double ans = 0;
                if(s[i-1]==t[j-1])
                {
                    ans =  dp[i-1][j-1]+dp[i-1][j];
                }
                else
                {
                    ans =  dp[i-1][j];
                }
                dp[i][j]=ans;
            }
        }
        return dp[n][m];
    }
};