// Last updated: 8/1/2026, 11:00:51 PM
class Solution {
public:
    int findLength(vector<int>& nums1, vector<int>& nums2) {
        //dp[i][j]=Length of maximum subarray ending at i-1 of s1 and ending at j-1 of s2
        //dp[i][j]=1+dp[i-1][j-1] if s1[i]==s2[j]
        int l1=nums1.size();
        int l2=nums2.size();
        vector<vector<int>> dp(l1+1,vector<int>(l2+1));
        int ans=0;
        for(int i=1;i<=l1;i++){
            for(int j=1;j<=l2;j++){
                int index1=i-1,index2=j-1;
                if(nums1[index1]==nums2[index2]){
                    dp[i][j]=1+dp[i-1][j-1];
                }
                ans=max(ans,dp[i][j]);
            }
        }
        return ans;
    }
};