// Last updated: 8/1/2026, 10:59:21 PM
class Solution {
public:
    const int mod=1e9+7;
    int numWays(vector<string>& words, string target) {
        //dp[i][j]=number of ways to form target till first i characters using first jth characters of any string in words
        // if we don't wish to match ith character of target with jth of any word in words the dp[i][j]=dp[i][j-1]
        //if target[i-1]==words[k][j-1] for any k, then we can take it and move to dp[i-1][j-1], actually it is number of ways to match target[i-1] with any of words[k][j-1], k is variable
        //then dp[i][j]=number of ways * dp[i-1][j-1]
        //dp[0][0]=1
        //dp[i][0]=1
        //dp[0][j]=0
        int n=words.size();
        int n1=words[0].size();
        int n2=target.size();
        vector<vector<int>> freq(n1,vector<int>(26));
        for(int i=0;i<n1;i++){
            for(int j=0;j<n;j++){
                freq[i][words[j][i]-'a']++;
            }
        }
        vector<vector<int>> dp(n1+1,vector<int>(n2+1));
        for(int i=0;i<=n1;i++){
            dp[i][0]=1;
        }

        for(int i=1;i<=n1;i++){
            for(int j=1;j<=n2;j++){
                int index1=i-1,index2=j-1;
                int frequency=freq[index1][target[index2]-'a'];
                long long int skip=dp[i-1][j]%mod;
                long long int match=(1LL*frequency*dp[i-1][j-1])%mod;
                dp[i][j]=(skip+match)%mod;
            }
        }
        return dp[n1][n2];
    }
};