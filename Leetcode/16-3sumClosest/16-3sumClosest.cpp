// Last updated: 7/22/2026, 9:26:27 PM
class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        sort(nums.begin(),nums.end());
        int n=nums.size();
        int ans=1e9;
        for(int i=0;i<n;i++){
            int l=i+1,r=n-1;
            while(l<r){
                if(nums[l]+nums[r]==target-nums[i]){//closest possible
                    ans=nums[i]+nums[l]+nums[r];
                    break;
                }else if(nums[l]+nums[r]<target-nums[i]){
                    if(abs(nums[i]+nums[l]+nums[r]-target)<abs(ans-target)){//update if closer sum found
                        ans=nums[i]+nums[l]+nums[r];
                    }
                    l++;//increase the sum to move closer
                }else{
                    if(abs(nums[i]+nums[l]+nums[r]-target)<abs(ans-target)){//update if closer sum found
                        ans=nums[i]+nums[l]+nums[r];
                    }
                    r--;//reduce the sum to move closer
                }
            }
        }
        return ans;
    }
};