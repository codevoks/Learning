// Last updated: 6/7/2026, 11:26:58 PM
class Solution {
public:
    bool f(int ind,string &A,vector<string> &B,vector<int> &dp)
{
    //cout<<" index is "<<ind<<" with remaining string "<<A.substr(ind)<<endl;
    if(ind==A.length())
    {
        //cout<<" inside base case with A = "<<A.substr(ind)<<endl;
        return true;
    }
        if(dp[ind]!=-1)
        {
            return dp[ind];
        }
    bool l=false;
    for(int i=ind+1;i<=A.length();i++)
    {
        string left=A.substr(ind,i-ind);
        if(find(B.begin(),B.end(),left)!=B.end())
        {
            //cout<<" left is "<<left<<endl;
            bool r=f(i,A,B,dp);
            //cout<<" r is "<<r<<endl;
            l=l||r;
        }
    }
    return dp[ind]=l;
}
    bool wordBreak(string s, vector<string>& wordDict) {
        //cout<<" length of string is "<<s.length()<<endl;
        vector<int> dp(s.length(),-1);
        return f(0,s,wordDict,dp);
    }
};