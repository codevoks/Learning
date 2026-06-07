// Last updated: 6/7/2026, 11:26:02 PM
class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int,int> nextGreater;
        stack<int> st;
        for(int i=nums2.size()-1;i>=0;i--){
            while(!st.empty()&&nums2[i]>nums2[st.top()]){
                st.pop();
            }
            nextGreater[nums2[i]]=!st.empty()?nums2[st.top()]:-1;
            st.push(i);
        }
        vector<int> ans;
        for(int i=0;i<nums1.size();i++){
            ans.push_back(nextGreater[nums1[i]]);
        }
        return ans;
    }
};