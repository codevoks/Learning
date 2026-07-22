// Last updated: 7/22/2026, 9:26:25 PM
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> ans;
        sort(nums.begin(),nums.end());
        int n=nums.size();
        int i=0;
        while(i<n){
            int first=nums[i];
            int j=i+1;
            while(j<n){
                int second=nums[j];
                int l=j+1,r=n-1;
                while(l<r){
                    int left=nums[l];
                    int right=nums[r];
                    long long int pairSum=1LL*left+right;
                    long long int requiredSum=1LL*target-first-second;
                    if(pairSum==requiredSum){
                        vector<int> current;
                        current.push_back(first);
                        current.push_back(second);
                        current.push_back(left);
                        current.push_back(right);
                        ans.push_back(current);
                        while(l<r&&nums[l]==left){
                            l++;
                        }
                        while(l<r&&nums[r]==right){
                            r--;
                        }
                    }else if(pairSum<requiredSum){
                        l++;
                    }else{
                        r--;
                    }
                }
                while(j<n&&nums[j]==second){
                    j++;
                }
            }
            while(i<n&&nums[i]==first){
                i++;
            }
        }
        return ans;
    }
};