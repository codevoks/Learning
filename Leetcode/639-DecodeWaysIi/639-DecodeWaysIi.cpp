// Last updated: 8/1/2026, 11:01:06 PM
class Solution {
public:
    const int mod=1e9+7;
    int numDecodings(string s) {
        //dp[i]=number of ways to decode string till index i
        int n=s.size();
        vector<int> dp(n+1);
        dp[0]=1;
        if(s[0]=='*'){
            dp[1]=9;
        }else if('1'<=s[0]&&s[0]<='9'){
            dp[1]=1;
        }
        for(int i=2;i<=n;i++){
            int index=i-1;
            long long int takeOne=0;
            long long int takeTwo=0;
            if(s[index]=='*'){
                takeOne=9LL*dp[i-1];
            }else if('1'<=s[index]&&s[index]<='9'){
                takeOne=dp[i-1];
            }else{
                takeOne=0;
            }
            if(s[index-1]=='*'&&s[index]=='*'){
                takeTwo=15LL*dp[i-2];
            }else if(s[index-1]=='0'){
                takeTwo=0;
            }else if(s[index-1]=='1'&&('0'<=s[index]&&s[index]<='9')){
                takeTwo=dp[i-2];
            }else if(s[index-1]=='1'&&s[index]=='*'){
                takeTwo=9LL*dp[i-2];
            }else if(s[index-1]=='2'&&('0'<=s[index]&&s[index]<='6')){
                takeTwo=dp[i-2];
            }else if(s[index-1]=='2'&&s[index]=='*'){
                takeTwo=6LL*dp[i-2];
            }else if(s[index-1]=='*'&&('0'<=s[index]&&s[index]<='6')){
                takeTwo=2LL*dp[i-2];
            }else if(s[index-1]=='*'&&('7'<=s[index]&&s[index]<='9')){
                takeTwo=dp[i-2];
            }
            takeOne=takeOne%mod;
            takeTwo=takeTwo%mod;
            dp[i]=(takeOne+takeTwo)%mod;
        }
        return (dp[n]+mod)%mod;
    }
};