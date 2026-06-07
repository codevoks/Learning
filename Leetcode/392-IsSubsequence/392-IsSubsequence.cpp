// Last updated: 6/7/2026, 11:26:10 PM
class Solution {
public:
    bool isSubsequence(string s, string t) {
        int n = s.size();
        int m = t.size();
        int i = 0,j = 0;
        while(i<n&&j<m)
        {
            char current = s[i];
            while(j<m&&current!=t[j])
            {
                j++;
            }
            if(j<m)
            {
                i++;
                j++;
            }
        }
        return (i==n);
    }
};