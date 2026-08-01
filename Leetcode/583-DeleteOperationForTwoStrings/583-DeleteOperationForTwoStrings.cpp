// Last updated: 8/1/2026, 11:01:10 PM
class Solution {
public:
    int minDistance(string word1, string word2) {
        //dp[i][j]=LCS of first i elements of str1 and first j elements of str2
        //dp[i][j]=1+dp[i-1][j-1] if str1[i-1]==str2[j-1]
        //dp[i][j]=max(dp[i][j-1],dp[i-1][j]) otherwise
        int n1=word1.size();
        int n2=word2.size();
        vector<vector<int>> dp(n1+1,vector<int>(n2+1));
        for(int i=1;i<=n1;i++){
            for(int j=1;j<=n2;j++){
                int index1=i-1,index2=j-1;
                if(word1[index1]==word2[index2]){
                    dp[i][j]=1+dp[i-1][j-1];
                }else{
                    dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
                }
            }
        }
        int lcs=dp[n1][n2];
        return n1-lcs+n2-lcs;
    }
};