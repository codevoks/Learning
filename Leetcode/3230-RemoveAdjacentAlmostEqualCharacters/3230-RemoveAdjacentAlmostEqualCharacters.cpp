// Last updated: 6/7/2026, 11:24:43 PM
class Solution {
public:
    int removeAlmostEqualCharacters(string word) {
        int i =0;
        int n = word.size();
        int ans = 0;
        while(i<n)
        {
            if(i-1>=0&&   (abs(word[i-1]-word[i])<=1))
            {
                ans++;
                i+=2;
            }
            else
            {
                i++;
            }
        }
        return ans;
    }
};