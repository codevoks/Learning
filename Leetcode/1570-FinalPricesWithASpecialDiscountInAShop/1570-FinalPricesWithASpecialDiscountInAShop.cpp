// Last updated: 6/7/2026, 11:25:00 PM
class Solution {
public:
    vector<int> finalPrices(vector<int>& prices) {
        int n = prices.size();
        vector<int> ans;
        for(int i = 0;i<n;i++){
            ans.push_back(prices[i]);
        }
        stack<int> st;
        for(int i = 0;i<n;i++){
            while(!st.empty()&&prices[st.top()]>=prices[i]){
                ans[st.top()]-=prices[i];
                st.pop();
            }
            st.push(i);
        }
        return ans;
    }
};
