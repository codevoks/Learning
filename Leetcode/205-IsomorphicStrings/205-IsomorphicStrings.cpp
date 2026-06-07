// Last updated: 6/7/2026, 11:26:33 PM
class Solution {
public:
    bool isIsomorphic(string s, string t) {
        map<char,char> mp,pm;
        int n = s.size();
        int m = t.size();
        for(int i =0;i<n;i++)
        {
            mp[s[i]]=t[i];
        }
        string ss="";
        for(int i =0;i<n;i++)
        {
            ss+=mp[s[i]];
        }
        for(int i =0;i<n;i++)
        {
            mp[t[i]]=s[i];
        }
        string tt="";
        for(int i =0;i<n;i++)
        {
            tt+=mp[t[i]];
        }
        return ss==t&&tt==s;
    }
};