// Last updated: 6/7/2026, 11:25:07 PM
class Solution {
public:
    string minRemoveToMakeValid(string s) {
        int n = s.length();
        stack<int> st;
        vector<int> remove(n,0);
        for(int i = 0;i<n;i++){
            if(s[i]=='('){
                st.push(i);
            } else if(s[i]==')'){
                if(st.empty()){
                    remove[i]=1;
                }else{
                    st.pop();
                }
            }
        }
        while(!st.empty()){
            remove[st.top()]=1;
            st.pop();
        }
        string ans;
        for(int i=0;i<n;i++){
            if(!remove[i]){
                ans+=s[i];
            }
        }
        return ans;
    }
};