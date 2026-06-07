// Last updated: 6/7/2026, 11:26:47 PM
class Solution {
public:
    string reverseWords(string s) {

        int n = s.size();
        string ans="";
        int i = n-1,j = n-1;
        while(i>=0&&j>=0)
        {
            while(i-1>=0&&s[i]==' ')
            {
                i--;
            }
            if(s[i]==' ')
            {
                break;
            }
            j = i;
            while(j-1>=0&&s[j-1]!=' ')
            {
                j--;
            }
            int len = i-j+1;
            string word = s.substr(j,len);
            ans = ans + word + " ";
            i=j-1;
        }
        n= ans.size();
        if(ans[n-1]==' ')
        {
            ans.pop_back();
        }
        return ans;
    }
};