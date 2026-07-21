// Last updated: 7/21/2026, 7:36:48 PM
class Solution {
public:
    int minimumMountainRemovals(vector<int>& nums) {
        int n=nums.size();
        vector<int> tails1,tails2;
        vector<int> inc(n),dec(n);
        int ans=0;
        for(int i=0;i<n;i++){
            auto it=lower_bound(tails1.begin(),tails1.end(),nums[i]);
            int pos=it-tails1.begin();
            inc[i]=pos+1;
            if(it!=tails1.end()){
                *it=nums[i];
            }else{
                tails1.push_back(nums[i]);
            }
        }
        for(int i=n-1;i>=0;i--){
            auto it=lower_bound(tails2.begin(),tails2.end(),nums[i]);
            int pos=it-tails2.begin();
            dec[i]=pos+1;
            if(it!=tails2.end()){
                *it=nums[i];
            }else{
                tails2.push_back(nums[i]);
            }
        }
        for(int i=0;i<n;i++){
            if(inc[i]>1&&dec[i]>1){
                ans=max(ans,inc[i]+dec[i]-1);
            }
        }
        return n-ans;
    }
};