// Last updated: 6/7/2026, 11:26:05 PM
class Solution {
public:
    int characterReplacement(string s, int k) {
        int n = s.length();
        unordered_map<char, int> frequency;
        int maxFrequency = 0;
        int i=0,j=0;
        int ans=0;
        while(j<n){
            frequency[s[j]]++;
            maxFrequency=max(maxFrequency,frequency[s[j]]);
            while((j-i+1)-maxFrequency>k){
                frequency[s[i]]--;
                i++;
            }
            ans = max(ans, j-i+1);
            j++;
        }
        return ans;
    }
};



