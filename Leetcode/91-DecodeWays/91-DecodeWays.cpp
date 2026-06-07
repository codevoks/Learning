// Last updated: 6/7/2026, 11:27:28 PM
class Solution {
public:
    int f(int ind,string A,vector<int> &dp)
{
    if(A.length()==0)
    {
        return 0;
    }
    if(A[ind]=='0')
    {
        return 0;
    }
    if(ind == A.length()-1)
    {
        return 1;
    }
    if(ind>=A.length())
    {
        return 1;
    }
        if(dp[ind]!=-1)
        {
            return dp[ind];
        }
    int sp= f(ind+1,A,dp);
    int tp = 0;
    if(A[ind]=='1'||(A[ind]=='2'&&48<=A[ind+1]&&A[ind+1]<=54))
    {
        tp = f(ind+2,A,dp);
    }
    return dp[ind]= sp+tp;
}
    int numDecodings(string s) {
        int n = s.length();
        vector<int> dp(n,-1);
    return f(0,s,dp);
    }
};