// Last updated: 6/9/2026, 9:29:13 PM
class Solution {
public:
    int integerBreak(int n) {
        //dp[i]=maximum product we can get by writing i as sum of at least k integers
        //dp[i]=maximum of j*dp[i-j], j*(i-j), where j varies from 1 to i-1
        //dp[1]=1
        vector<int> dp(n+1,0);
        dp[0]=0;
        dp[1]=1;
        for(int i=2;i<=n;i++){
            for(int j=i-1;j>=1;j--){
                dp[i]=max(dp[i],max(j*dp[i-j], j*(i-j)));
            }
        }
        for(auto it:dp){
            cout<<it<<" ";
        }
        return dp[n];
    }
};

/*
dp[0]=0
dp[1]=1
dp[2]=max{1*dp[1], 1*1}=1
dp[3]=max{1*dp[2], 1*2, 2*dp[1], 2*1}=max{1, 2, 2, 2}=2
dp[4]=max{1*dp[3], 1*3, 2*dp[2], 2*2, 3*dp[1], 3*1}=max{2, 3, 2, 4, 3, 3}=4

*/

/*
brute force = for any n try to write it a sum of 1, 2, 3, 4...n integers and take maximum product, but here number of
*/