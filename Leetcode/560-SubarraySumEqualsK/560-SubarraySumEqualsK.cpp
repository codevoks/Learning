// Last updated: 7/13/2026, 8:23:44 PM
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        //since here numbers can be negative so we cannot use sliding window
        //Otherthing that strikes your mind when you hear subarray sum ? prefix ? right ?
        int n=nums.size();
        unordered_map <int,int> sumFreq;
        sumFreq[0]++;
        int sum=0;
        int ans=0;
        for(int r=0;r<n;r++){
            //include r
            sum+=nums[r];

            //check if we have a value in prefix such that prefix[r]-prefix[l-1]==k
            if(sumFreq[sum-k]>0){
                ans+=sumFreq[sum-k];
            }
            //note that we are updating after updaing the answer otherwise empty subarray will also be counted
            sumFreq[sum]++;
        }
        return ans;
    }
};