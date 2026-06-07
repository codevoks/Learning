// Last updated: 6/7/2026, 11:27:00 PM
class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        if(accumulate(gas.begin(),gas.end(),0) < accumulate(cost.begin(),cost.end(),0))
        {
            return -1;
        }
        vector<int> d;
        for(int i = 0;i<gas.size();i++)
        {
            d.push_back(gas[i]-cost[i]);
        }
        int total=0;
        int c=0;
        for(int i = 0;i<gas.size();i++)
        {
            total=total+d[i];
            if(total<0)
            {
                c=i+1;
                total=0;
            }
        }
        return c;
    }
};