// Last updated: 6/7/2026, 11:27:40 PM
class Solution {
public:
    int lengthOfLastWord(string s) {
        int n = s.size();
        int i = n-1;
        int j = n-1;
        //while(i>=0&&i>=0)
        //{
            while(i>=0&&s[i]==' ')
            {
                i--;
            }
            j = i;
            while(j>=0&&s[j]!=' ')
            {
                j--;
            }
        //}
        return i-j;
    }
};