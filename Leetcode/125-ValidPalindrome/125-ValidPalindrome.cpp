// Last updated: 6/7/2026, 11:27:05 PM
class Solution {
public:
    bool isPalindrome(string s) {
        int n = s.size();
        int i = 0, j = n-1;
        int flag = 1;
        while(i<=j)
        {
            while(i<n&&!isalnum(s[i]))
            {
                i++;
            }
            if(i<n)
            {
                s[i]=tolower(s[i]);
            }
            while(j>=0&&!isalnum(s[j]))
            {
                j--;
            }
            if(j>=0)
            {
                s[j]=tolower(s[j]);
            }
            if(i<=j&&s[i]!=s[j])
            {
                return 0;
            }
            i++;
            j--;
        }
        return 1;
    }
};