// Last updated: 6/7/2026, 11:27:58 PM
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        int ind = 0;
        string s="";
        int n = strs.size();
        while(ind<strs[0].size())
        {
            int flag = 1;
            for(int i = 0;i<n-1;i++)
            {
                int l = strs[i].size();
                int ln = strs[i+1].size();
                if((ind>l)||(ind>ln)||(strs[i][ind]!=strs[i+1][ind]))
                {
                    flag = 0;
                    break;
                }
            }
            if(flag)
            {
                s+=strs[0][ind];
                ind++;
            }
            else
            {
                break;
            }
        }
        return s;
    }
};