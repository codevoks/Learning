// Last updated: 6/7/2026, 11:26:21 PM
class Solution {
public:
    bool isAnagram(string s, string t) {
        int n=s.size();
        int m = t.size();
        map<char,int> mp;
        for(int i =0;i<n;i++)
        {
            mp[s[i]]++;
        }
        for(int i = 0;i<m;i++)
        {
            mp[t[i]]--;
        }
        if(n!=m)
        {
            return 0;
        }
        for(auto it:mp)
        {
            if(it.second<0)
            {
                return 0;
            }
        }
        return 1;
    }
};