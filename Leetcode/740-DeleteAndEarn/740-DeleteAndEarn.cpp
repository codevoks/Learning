// Last updated: 6/11/2026, 9:49:24 PM
class Solution {
public:
    int deleteAndEarn(vector<int>& nums) {
        //dp[i] can be used but the constraint is on values not index, so we need indices of those values but that is independent of ith index's value
        unordered_map<int,int> freq;
        int n=nums.size();
        for(int i=0;i<n;i++){
            freq[nums[i]]++;
        }
        int prev2=1*freq[1];
        int prev1=max(prev2, 2*freq[2]);
        for(int i=3;i<=10000;i++){
            int cur=max(prev2+i*freq[i],prev1);
            prev2=prev1;
            prev1=cur;
        }
        return prev1;
    }
};