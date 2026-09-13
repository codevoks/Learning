// Last updated: 9/13/2026, 9:02:51 AM
class Solution {
public:
    int countNumbersWithUniqueDigits(int n) {
        //dp[i]=number of positive numbers of i digits, all being unique
        //for 0 we have to manually add as it is not positive
        if(n==0){
            return 1;
        }
        vector<int> dp(n+1);
        dp[1]=9;
        for(int i=2;i<=n;i++){
            dp[i]=dp[i-1]*(11-i);
        }
        int ans=1;
        for(int i=1;i<=n;i++){
            ans+=dp[i];
        }
        return ans;
    }
};