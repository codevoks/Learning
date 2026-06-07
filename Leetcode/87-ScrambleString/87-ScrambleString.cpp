// Last updated: 6/7/2026, 11:27:31 PM
class Solution {
public:
    int f(string s1,string s2,unordered_map <string,bool> &dp)
    {
        if(s1.length()!=s2.length())
        {
            return false;
        }
        if(s1.length()==0&&s2.length()==0)
        {
            return true;
        }
        if(s1.length()==1&&s2.length()==1)
        {
            return s1[0]==s2[0];
        }
        if(s1==s2)
        {
            return true;
        }
        string k = s1+" "+s2;
        if(dp.count(k)>0)
        {
            return dp[k];
        }
        int n = s1.length();
        bool con1=false,con2=false;
        for(int i = 1;i<n;i++)
        {
            con1=f(s1.substr(0,i),s2.substr(n-i,i),dp)&&f(s1.substr(i,n-i),s2.substr(0,n-i),dp);
            con2=f(s1.substr(0,i),s2.substr(0,i),dp)&&f(s1.substr(i,n-i),s2.substr(i,n-i),dp);
            if(con1||con2)
            {
                dp[k]=con1||con2;
            }
        }
        return dp[k];
    }
    bool isScramble(string s1, string s2) {
        unordered_map <string,bool> dp;
        return f(s1,s2,dp);
    }
};