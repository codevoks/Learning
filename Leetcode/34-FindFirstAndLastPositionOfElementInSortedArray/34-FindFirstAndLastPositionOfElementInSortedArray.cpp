// Last updated: 7/10/2026, 10:51:04 PM
class Solution {
public:
    int isValid(auto it,vector<int>& nums){
        return (nums.begin()<=it && it<nums.end());
    }
    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int> ans;
        ans.push_back(-1);
        ans.push_back(-1);
        if(!nums.size()){
            return ans;
        }
        auto lb = lower_bound(nums.begin(),nums.end(),target);
        auto ub = upper_bound(nums.begin(),nums.end(),target);
        ub--;
        if(!isValid(lb,nums) || !isValid(ub,nums) || *lb!=target || *ub!=target){
            return ans;
        }
        ans[0]=(lb-nums.begin());
        ans[1]=(ub-nums.begin());
        return ans;
    }
};