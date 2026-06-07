// Last updated: 6/7/2026, 11:27:46 PM
class Solution 
{
public:
    int f(int i,int j,string &s,string &p,vector<vector<int>> &dp)
    {
        if(i==0&&j==0)
        {
            return true;
        }
        if(i>0&&j==0)
        {
            return false;
        }
        if(i==0&&j>0)
        {
            for(int k = 1;k<=j;k++)
            {
                if(p[k-1]!='*')
                {
                    return false;
                }
            }
            return true;
        }
        if(dp[i][j]!=-1)
        {
            return dp[i][j];
        }
        bool ans = false;
        if(s[i-1]==p[j-1]||p[j-1]=='?')
        {
            ans = f(i-1,j-1,s,p,dp);
        }
        if(p[j-1]=='*')
        {
            ans = f(i-1,j,s,p,dp)||f(i,j-1,s,p,dp);
        }
        return dp[i][j]=ans;
    }
    bool isMatch(string s, string p) 
    {
        int n = s.length();
        int m = p.length();
        vector<vector<int>> dp(n+1,vector<int>(m+1));
        //return f(n,m,s,p,dp);
        dp[0][0]=1;
        for(int i =1;i<=n;i++)
        {
            dp[i][0]=0;
        }
        for(int j=1;j<=m;j++)
        {
            dp[0][j] = 1;
            for(int k = 1;k<=j;k++)
            {
                if(p[k-1]!='*')
                {
                    dp[0][j]=0;
                    break;
                }
            }
        }
        for(int i = 1;i<=n;i++)
        {
            for(int j = 1;j<=m;j++)
            {
                bool ans = false;
                if(s[i-1]==p[j-1]||p[j-1]=='?')
                {
                    ans = dp[i-1][j-1];
                }
                if(p[j-1]=='*')
                {
                    ans = dp[i-1][j]||dp[i][j-1];
                }
                dp[i][j]=ans;
            }
        }
        return dp[n][m];
    }
};