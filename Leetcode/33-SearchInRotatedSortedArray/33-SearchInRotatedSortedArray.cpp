// Last updated: 7/10/2026, 10:51:06 PM
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int n=nums.size();
        int lb=0;
        int ub=n-1;
        int shift=-1;
        int k=0;
        while(lb<=ub){
            int mid = lb+(ub-lb)/2;
            if(nums[mid]<nums[0]){
                shift=mid;
                ub=mid-1;
            }else{
                lb=mid+1;
            }
        }
        if(shift!=-1){
            k=n-shift;
        }
        sort(nums.begin(),nums.end());
        auto it=lower_bound(nums.begin(),nums.end(),target);
        if(it==nums.end()||*it!=target){
            return -1;
        }
        int index=it-nums.begin();
        if(index-k>=0){
            return index-k;
        }
        return n+index-k;
    }
};