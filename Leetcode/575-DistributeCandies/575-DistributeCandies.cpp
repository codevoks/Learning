// Last updated: 6/7/2026, 11:25:55 PM
class Solution {
public:
    int distributeCandies(vector<int>& candyType) {
        set<int> s(candyType.begin(),candyType.end());
        int types = s.size();
        int n = candyType.size();
        if(types<=n/2)
        {
            return types;
        }
        return n/2;
    }
};