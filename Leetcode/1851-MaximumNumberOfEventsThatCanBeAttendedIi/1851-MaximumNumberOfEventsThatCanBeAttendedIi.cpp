// Last updated: 7/25/2026, 10:16:02 PM
class Solution {
public:
    static bool compare(vector<int>& a, vector<int>& b){
        return a[1]<b[1];
    }
    int maxValue(vector<vector<int>>& events, int k) {
        //dp[i][k]=maximum profit till index i using at most k resources
        //dp[i]=max(not take, take)
        //not take=dp[i-1][k]
        //take=profit[i]+dp[lastvalidIndex][k]
        sort(events.begin(),events.end(),compare);
        int n=events.size();
        vector<vector<int>> dp(n+1,vector<int>(k+1,0));
        //optimised O(nlogn+nk) first find the valid index and then fill k
        for(int i=1;i<=n;i++){
            int index=i-1;
            int current=events[index][2];
            int lastValidIndex=-1;
            int l=0,h=index-1;
            while(l<=h){
                int mid=l+(h-l)/2;
                if(events[mid][1]<events[index][0]){
                    lastValidIndex=mid;
                    l=mid+1;
                }else{
                    h=mid-1;
                }
            }
            for(int j=1;j<=k;j++){
                int take=current;
                if(lastValidIndex!=-1){
                    take+=dp[lastValidIndex+1][j-1];
                }
                int notTake=dp[i-1][j];
                dp[i][j]=max(take,notTake);
            }
        }
        return dp[n][k];

        //below code runs is suboptimal O(nklogn)
        // for(int i=1;i<=n;i++){
        //     int index=i-1;
        //     int current=events[index][2];
        //     for(int j=1;j<=k;j++){
        //         int lastValidIndex=-1;
        //         int l=0,h=index-1;
        //         while(l<=h){
        //             int mid=l+(h-l)/2;
        //             if(events[mid][1]<events[index][0]){
        //                 lastValidIndex=mid;
        //                 l=mid+1;
        //             }else{
        //                 h=mid-1;
        //             }
        //         }
        //         int take=current;
        //         if(lastValidIndex!=-1){
        //             take+=dp[lastValidIndex+1][j-1];
        //         }
        //         int notTake=dp[i-1][j];
        //         dp[i][j]=max(take,notTake);
        //     }
        // }
        // return dp[n][k];
    }
};