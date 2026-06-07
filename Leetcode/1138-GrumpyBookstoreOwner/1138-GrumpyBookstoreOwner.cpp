// Last updated: 6/7/2026, 11:25:11 PM
class Solution {
public:
    int maxSatisfied(vector<int>& customers, vector<int>& grumpy, int minutes) {
        int n=customers.size();
        vector<int> prefix;
        int base=0;
        for(int i = 0;i<n;i++){
            base+=((!grumpy[i])*customers[i]);
        }
        for(int i=0;i<n;i++){
            prefix.push_back((customers[i]*grumpy[i])+((i>0)?prefix[i-1]:0));
        }
        int extra=0;
        for(int i=0;i<n-minutes+1;i++){
            int temp = prefix[i+minutes-1]-((i>0)?prefix[i-1]:0);
            extra=max(extra, temp);
        }
        return base+extra;
    }
};