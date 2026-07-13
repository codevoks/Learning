// Last updated: 7/13/2026, 8:52:57 PM
class Solution {
public:
    void reverseString(vector<char>& s) {
        int n=s.size();
        int i=0,j=n-1;
        while(i<j){
            swap(s[i],s[j]);
            i++;
            j--;
        }
    }
};