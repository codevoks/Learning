// Last updated: 6/7/2026, 11:26:08 PM
class Solution {
public:
    string decodeString(string s) {
        int n = s.length();
        stack<pair<string,int>> st;
        string curr = "";
        int num = 0;
        for(int i = 0;i<n;i++){
            if(isdigit(s[i])){
                num=10*num+(s[i]-'0');
            }else if(s[i]=='['){
                st.push({curr,num});
                num=0;
                curr="";
            }else if(s[i]==']'){
                string pre = st.top().first;
                int repeat = st.top().second;
                st.pop();
                string newString = "";
                for(int i = 0;i<repeat;i++){
                    newString+=curr;
                }
                curr=pre+newString;
            }else{
                curr=curr+s[i];
            }
        }
        return curr;
    }
};