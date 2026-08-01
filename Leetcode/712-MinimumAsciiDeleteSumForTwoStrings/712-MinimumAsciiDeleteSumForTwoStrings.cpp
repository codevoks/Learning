// Last updated: 8/1/2026, 11:00:53 PM
class Solution {
public:
    int ASCIIweight(string s){
        int n=s.size();
        int ans=0;
        for(int i=0;i<n;i++){
            ans+=(int)s[i];
        }
        return ans;
    }
    int minimumDeleteSum(string s1, string s2) {
        //dp[i][j]=maximum sum CS using first i elements of s1 and first j elements of s2
        //dp[i][j]=str1[i-1]+dp[i-1][j-1]
        //dp[i][j]=max(dp[i-1][j],dp[i][j-1])
        int n1=s1.size();
        int n2=s2.size();
        vector<vector<int>> dp(n1+1,vector<int>(n2+1));
        for(int i=1;i<=n1;i++){
            for(int j=1;j<=n2;j++){
                int index1=i-1,index2=j-1;
                if(s1[index1]==s2[index2]){
                    dp[i][j]=(int)s1[index1]+dp[i-1][j-1];
                }else{
                    dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
                }
            }
        }
        int lcs=dp[n1][n2];
        int weight1=ASCIIweight(s1);
        int weight2=ASCIIweight(s2);
        return weight1+weight2-2*lcs;
    }
};