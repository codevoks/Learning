// Last updated: 8/1/2026, 11:00:13 PM
class Solution {
public:
    const int mod=1e9+7;
    int distinctSubseqII(string s) {
        //dp[i]=number of distinct non-empty subsequences using the first i characters of s
        int n=s.size();
        vector<int> dp(n+1);
        vector<int> lastOccurence(26,-1);
        for(int i=1;i<=n;i++){
            int index=i-1;
            long long int duplicate=0;
            int previousOccurence=lastOccurence[s[index]-'a'];
            if(previousOccurence!=-1){
                int previousIndex=previousOccurence+1;
                duplicate=(dp[previousIndex-1]+1)%mod;
            }
            long long int old=dp[i-1]%mod;
            long long int append=dp[i-1]%mod;
            int singleCharacter=1;
            dp[i]=(old+append+singleCharacter-duplicate)%mod;
            lastOccurence[s[index]-'a']=index;
        }
        return (dp[n]+mod)%mod;
    }
};