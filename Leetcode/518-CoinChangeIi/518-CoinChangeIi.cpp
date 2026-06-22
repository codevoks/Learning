// Last updated: 6/22/2026, 9:25:02 PM
class Solution {
    /*
        0/1: take from prev[j - x]
        Unbounded: take from cur[j - x]
    */
public:
    int change(int amount, vector<int>& coins) {
        //dp[i][j]=number of ways to make up the amount 5 using first i coins any number of times
        //dp[i][j]=dp[i-1][j];if(j>=num[i-1]){dp[i][j]+=dp[i-1][j-num[i-1]];
        //dp[0][0]=1
        //dp[0][j]=0
        int n=coins.size();
        vector<unsigned int> prev(amount+1,0);
        prev[0]=1;
        for(int i=1;i<=n;i++){
            int element=coins[i-1];
            vector<unsigned int> cur(amount+1,0);
            for(int j=0;j<=amount;j++){
                cur[j]=prev[j];
                if(j-element>=0){
                    cur[j]+=cur[j-element];
                }
            }
            prev=cur;
        }
        return prev[amount];
    }
};