// Last updated: 9/13/2026, 9:00:42 AM
class Solution {
public:
    int maxSumAfterPartitioning(vector<int>& arr, int k) {
        //dp[i]=max sum after partition with first i elements. i ranges from 0 to n
        //dp[i]=max over all j's in dp[j]+max(arr[j+1-1...i-1])*(i-j)), i-j<=k, 0<=j<i
        //dp[0]=0

        int n=arr.size();
        vector<int> dp(n+1,0);
        dp[0]=0;
        for(int i=1;i<=n;i++){
            int maximum=-1;
            for(int j=i-1;j>=0;j--){
                maximum=max(maximum,arr[j]);
                int subaraySize=i-j;
                if(subaraySize<=k){
                    dp[i]=max(dp[i],dp[j]+subaraySize*maximum);
                }
            }
        }
        return dp[n];
    }
};