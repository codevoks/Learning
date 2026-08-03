// Last updated: 8/3/2026, 9:53:58 PM
class Solution {
public:
    int n;
    int minimumXORSum(vector<int>& nums1, vector<int>& nums2) {
        //dp[mask]=maximum XOR sum, where mask represents the elements in nums1 matched with nums2
        int n=nums1.size();
        vector<vector<int>> score(n,vector<int>(n));
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                score[i][j]=nums1[i]^nums2[j];
            }
        }
        const int INF=1e9;
        vector<long long int> dp(1<<n,INF);
        dp[0]=0;
        int finalState=(1<<n)-1;
        for(int mask=1;mask<=finalState;mask++){
            int lastElementMatched=__builtin_popcountll(mask)-1;
            for(int j=0;j<n;j++){//try on all j
                if(!(mask&(1<<j))){//skip j's that we cannot remove
                    continue;
                }
                int previousMask=(mask&~(1<<j));
                dp[mask]=min(dp[mask],dp[previousMask]+1LL*score[lastElementMatched][j]);//take minimum XOR sum with current nums1 element against all the nums2 elements
            }
        }
        return dp[finalState];
    }
};