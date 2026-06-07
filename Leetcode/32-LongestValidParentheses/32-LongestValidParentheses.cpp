// Last updated: 6/7/2026, 11:27:49 PM
class Solution {
public:
    int longestValidParentheses(string s) {
        int n = s.length();
        stack<int> st;
        st.push(-1);
        int ans = 0;
        for(int i=0;i<n;i++){
            if(s[i]==')'){
                st.pop();
                if(st.empty()){
                    st.push(i);
                }else{
                    ans=max(ans,i-st.top());
                }
            }else{
                st.push(i);
            }
        }
        return ans;
    }
};