// Last updated: 6/7/2026, 11:28:00 PM
class Solution {
public:
    int maxArea(vector<int>& height) {
        long long int ans = 0;
        int i = 0, j = height.size()-1;
        while(i<j){
            long long int area = min(height[i],height[j])*(j-i);
            ans = max(area,ans);
            if(height[i]<height[j]){
                i++;
            }else{
                j--;
            }
        }
        return ans;
    }
};