// Last updated: 6/7/2026, 11:28:03 PM
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map <char,int> frequency;
        int n = s.length();
        int j = 0,i=0;
        int ans = 0;
        while(j<n){
            frequency[s[j]]++;
            while(frequency[s[j]]>1){
                frequency[s[i]]--;
                i++;
            }
            ans = max(ans,j-i+1);
            j++;
        }
        return ans;
    }
};