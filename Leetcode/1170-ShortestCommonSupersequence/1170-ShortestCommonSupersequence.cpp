// Last updated: 8/1/2026, 10:59:44 PM
class Solution {
public:
    string shortestCommonSupersequence(string str1, string str2) {
        //dp[i][j]=LCS using first i elements of str1 and first j of str2
        //dp[i][j]=1+dp[i-1][j-1]
        //dp[i][j]=max(dp[i-1][j],dp[i][j-1])
        int n1=str1.size();
        int n2=str2.size();
        vector<vector<int>> dp(n1+1,vector<int>(n2+1));
        for(int i=1;i<=n1;i++){
            for(int j=1;j<=n2;j++){
                int index1=i-1,index2=j-1;
                if(str1[index1]==str2[index2]){
                    dp[i][j]=1+dp[i-1][j-1];
                }else{
                    dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
                }
            }
        }
        string ans="";
        int i=n1,j=n2;
        while(i>0&&j>0){
            int index1=i-1,index2=j-1;
            if(str1[index1]==str2[index2]){
                ans+=str1[index1];
                i--;
                j--;
            }else if(dp[i-1][j]>dp[i][j-1]){
                ans+=str1[index1];
                i--;
            }else{
                ans+=str2[index2];
                j--;
            }
        }
        while(i>0){
            int index1=i-1;
            ans+=str1[index1];
            i--;
        }
        while(j>0){
            int index2=j-1;
            ans+=str2[index2];
            j--;
        }
        reverse(ans.begin(),ans.end());
        return ans;
    }
};