// Last updated: 6/7/2026, 11:26:11 PM
class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        int n = ransomNote.size();
        int m = magazine.size();
        map<char,int> mp;
        for(int i = 0;i<m;i++)
        {
            mp[magazine[i]]++;
        }
        for(int i = 0;i<n;i++)
        {
            mp[ransomNote[i]]--;
        }
        int ans = 1;
        for(auto it:mp)
        {
            if(it.second<0)
            {
                return 0;
            }
        }
        return ans;
    }
};