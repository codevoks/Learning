// Last updated: 7/25/2026, 10:27:32 PM
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        //dp[i][j]=Length of LCS using first i elements of s1 and first j elements of s2
        //dp[i][j]=1+dp[i-1][j-1] if s1[i]==s2[j]
        //dp[i][j]=max(dp[i-1][j],dp[i][j-1])
        int l1=text1.size();
        int l2=text2.size();
        vector<vector<int>> dp(l1+1,vector<int>(l2+1));
        for(int i=1;i<=l1;i++){
            for(int j=1;j<=l2;j++){
                int index1=i-1,index2=j-1;
                if(text1[index1]==text2[index2]){
                    dp[i][j]=1+dp[i-1][j-1];
                }else{
                    dp[i][j]=max(dp[i][j-1],dp[i-1][j]);
                }
            }
        }
        return dp[l1][l2];
    }
};