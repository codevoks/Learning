// Last updated: 9/13/2026, 9:00:11 AM
class Solution {
public:
    int n=0;
    int isInvalid(int odds,int k){
        return odds>k;
    }
    int atMostKOdd(vector<int>& nums, int k){
        if(k<0){
            return 0;
        }
        int l=0;
        int odds=0;
        int ans=0;
        for(int r=0;r<n;r++){
            //include r
            odds+=(nums[r]%2);

            while(isInvalid(odds,k)){
                odds-=(nums[l]%2);
                l++;
            }

            ans+=(r-l+1);
        }
        return ans;
    }
    int numberOfSubarrays(vector<int>& nums, int k) {
        n=nums.size();
        return atMostKOdd(nums,k)-atMostKOdd(nums,k-1);
    }
};