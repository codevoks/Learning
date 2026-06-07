// Last updated: 6/7/2026, 11:26:07 PM
class Solution {
public:
    string removeKdigits(string num, int k) {
        int n = num.length();
        stack<char> st;
        for(int i = 0;i<n;i++){
            while(!st.empty()&&(st.top()>num[i])&&k){
                st.pop();
                k--;
            }
            st.push(num[i]);
        }
        while(!st.empty()&&k){
            st.pop();
            k--;
        }
        string ans="";
        while(!st.empty()){
            ans+=st.top();
            st.pop();
        }
        reverse(ans.begin(),ans.end());
        int ind=ans.length();
        for(int i = 0;i<ans.length();i++){
            if(ans[i]!='0'){
                ind = i;
                break;
            }
        }
        ans = ind<ans.length()?ans.substr(ind):"";
        return ans.length()? ans: "0";
    }
};