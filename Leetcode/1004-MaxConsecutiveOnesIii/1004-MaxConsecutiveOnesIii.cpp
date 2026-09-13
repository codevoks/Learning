// Last updated: 9/13/2026, 9:00:55 AM
class Solution {
public:
    int isValid(int flipped, int k){
        return flipped<=k;
    }
    int longestOnes(vector<int>& nums, int k) {
        int n=nums.size();
        int j=0;
        int flipped=0;
        int ans=0;
        for(int i=0;i<n;i++){
            //take the current element
            if(nums[i]==0){
                flipped++;
            }

            //if current subarray is invalid then moving i to right won't fix it, so shrink left
            while(!isValid(flipped,k)){
                if(nums[j]==0){
                    flipped--;
                }
                j++;
            }

            //check if this is the answer
            ans=max(ans,i-j+1);
        }
        return ans;
    }
};