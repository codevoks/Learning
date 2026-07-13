// Last updated: 7/13/2026, 8:22:48 PM
class Solution {
public:
    int n=0;
    int longestSubarray(vector<int>& nums, int limit) {
        //for a given window if we try to include a new element then the absolute difference of min and max can never decrease, so if it is more than limit then we have to move the left pointer
        n=nums.size();
        int l=0;
        deque<int> minDeq;
        deque<int> maxDeq;
        int ans=0;
        for(int r=0;r<n;r++){
            //include r
            while(!minDeq.empty() && nums[minDeq.back()]>nums[r]){
                minDeq.pop_back();
            }
            while(!maxDeq.empty() && nums[maxDeq.back()]<nums[r]){
                maxDeq.pop_back();
            }
            minDeq.push_back(r);
            maxDeq.push_back(r);

            while(!minDeq.empty()&&!maxDeq.empty()&&(abs(nums[maxDeq.front()]-nums[minDeq.front()])>limit)){
                if(!minDeq.empty()&&minDeq.front()==l){
                    minDeq.pop_front();
                }
                if(!maxDeq.empty()&&maxDeq.front()==l){
                    maxDeq.pop_front();
                }
                l++;
            }

            ans=max(ans,r-l+1);
        }
        return ans;
    }
};