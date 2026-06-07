// Last updated: 6/7/2026, 11:25:53 PM
class Solution {
public:
    double findMaxAverage(vector<int>& nums, int k) {
        double ans = -1e9;
        vector<long long int> prefix;
        long long int sum = 0;
        int n = nums.size();
        for(int i=0;i<n;i++){
            sum+=nums[i];
            prefix.push_back(sum);
        }
        for(int j = k-1;j<n;j++){
            long long int prefixSum = prefix[j]-((j>=k)?prefix[j-k]:0);
            double average = (1.0*prefixSum)/k;
            ans = max(average,ans);
        }
        return ans;
    }
};