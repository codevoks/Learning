// Last updated: 6/7/2026, 11:27:57 PM
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> ans;
        sort(nums.begin(),nums.end());
        int n = nums.size();
        int i=0;
        cout<<"pre"<<"\n";
        while(1){
            cout<<"loop"<<"\n";
            int target = -nums[i];
            cout<<"target is "<<target<<"\n";
            int j = i+1, k = n-1;
            while((i<j)&&(j<k)&&(k<n)){
                if(nums[j]+nums[k]<target){
                    j++;
                }else if(nums[j]+nums[k]>target){
                    k--;
                }else{
                    vector<int> current;
                    current.push_back(nums[i]);
                    current.push_back(nums[j]);
                    current.push_back(nums[k]);
                    cout<<" indices i= "<<i<<" j= "<<j<<" & k= "<<k<<"\n";
                    cout<<" for "<<nums[i]<<" adding "<<nums[j]<<" & "<<nums[k]<<"\n";
                    ans.push_back(current);
                    while(j<k&&(nums[j]==nums[j+1])){
                        j++;
                    }
                    while(j<k&&(nums[k-1]==nums[k])){
                        k--;
                    }
                    j++;
                    k--;
                }
            }
            while((i<n-3)&&(nums[i]==nums[i+1])){
                i++;
                cout<<"moving i to "<<i<<"\n";
            }
            i++;
            if(i>n-3){
                break;
            }
        }
        return ans;
    }
};