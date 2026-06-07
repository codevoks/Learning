// Last updated: 6/7/2026, 11:27:20 PM
class Solution {
public:
    
    int f(string a,string b,string c,int x,int y,int z,vector<vector<int>> &dp)
    {
        if(x+y!=z)
        {
            return 0;
        }
        if(x==0&&y==0&&z==0)
        {
            return 1;
        }
        if(z==0&&(x!=0||y!=0))
        {
            return 0;
        }
        if(dp[x][y]!=-1)
        {
            return dp[x][y];
        }
        bool m=false,n=false;
        if(x>=1&&z>=1&&c[z-1]==a[x-1])
        {
            n=f(a,b,c,x-1,y,z-1,dp);
        }
        if(y>=1&&z>=1&&c[z-1]==b[y-1])
        {
            m=f(a,b,c,x,y-1,z-1,dp);
        }
        return dp[x][y]=m||n;
    }
    bool isInterleave(string s1, string s2, string s3) 
    {
        int x=s1.length();
        int y=s2.length();
        int z=s3.length();
        vector<vector<int>> dp(x+1,vector<int> (y+1,-1));
        return f(s1,s2,s3,x,y,z,dp);
    }
};