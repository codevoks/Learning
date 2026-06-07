// Last updated: 6/7/2026, 11:24:49 PM
class Solution {
public:
    vector<int> findIntersectionValues(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        int m = nums2.size();
        unordered_map<int,int> mp1;
        for(int i = 0;i<n;i++)
        {
            mp1[nums1[i]]++;
        }
        unordered_map<int,int> mp2;
        for(int i = 0;i<m;i++)
        {
            mp2[nums2[i]]++;
        }
        int a=0;
        for(int i =0;i<n;i++)
        {
            if(mp2[nums1[i]]>0)
            {
                a++;
            }
        }
        int b=0;
        for(int i =0;i<m;i++)
        {
            if(mp1[nums2[i]]>0)
            {
                b++;
            }
        }
        vector<int> ans;
        ans.push_back(a);
        ans.push_back(b);
        return ans;
    }
};