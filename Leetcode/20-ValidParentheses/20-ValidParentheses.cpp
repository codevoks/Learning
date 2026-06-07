// Last updated: 6/7/2026, 11:27:55 PM
class Solution {
public:
    bool isValid(string s) {
        int n = s.size();
        map<char,int> mp;
        stack<int> st;
        mp['(']=1;
        mp[')']=-1;
        mp['{']=2;
        mp['}']=-2;
        mp['[']=3;
        mp[']']=-3;

        int flag = 1;
        for(int i = 0;i<n;i++)
        {
            int current = mp[s[i]];
            if(!st.empty())
            {
                if(current>0)
                {
                    st.push(current);
                }
                else
                {
                    if(current+st.top()==0)
                    {
                        st.pop();
                    }
                    else
                    {
                        flag=0;
                        break;
                    }
                }
            }
            else
            {
                if(current>0)
                {
                    st.push(current);
                }
                else
                {
                    flag=0;
                    break;
                }
            }
        }
        if(!st.empty())
        {
            flag=0;
        }
        return flag;
    }
};