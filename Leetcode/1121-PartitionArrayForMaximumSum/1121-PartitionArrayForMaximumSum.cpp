// Last updated: 6/7/2026, 11:25:12 PM
class Solution {
public:
    int maxSumAfterPartitioning(vector<int>& arr, int k) {
        int n=arr.size();
        vector<int> dp(n,-1);
        dp[0]=arr[0];
        for(int i=1;i<n;i++){
            //try all the sizes of partitions including the ith element
            int maximumElement=arr[i];
            for(int j=1;j<=min(i+1,k);j++){
                maximumElement=max(maximumElement,arr[i-j+1]);
                dp[i]=max(dp[i],maximumElement*j+(i<j?0:dp[i-j]));
            }
        }
        return dp[n-1];
    }
};