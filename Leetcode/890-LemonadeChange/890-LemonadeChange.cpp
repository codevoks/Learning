// Last updated: 6/7/2026, 11:25:32 PM
class Solution {
public:
    bool lemonadeChange(vector<int>& bills) {
        int n = bills.size();
        map<int,int> mp;
        mp[5]=0;
        mp[10]=0;
        mp[20]=0;
        for(int i = 0;i<n;i++)
        {
            if(bills[i]==5)
            {
                mp[5]++;
            }
            else if(bills[i]==10)
            {
                if(mp[5]>=1)
                {
                    mp[5]=mp[5]-1;
                    mp[10]++;
                }
                else
                {
                    return 0;
                }
            }
            else// bills[i] == 20
            {
                if(mp[5]>=3||(mp[10]>=1&&mp[5]>=1))
                {
                    if(mp[10]>=1&&mp[5]>=1)
                    {
                        mp[20]++;
                        mp[10]--;
                        mp[5]--;
                    }
                    else
                    {
                        mp[20]++;
                        mp[5]=mp[5]-3;
                    }
                }
                else
                {
                    return 0;
                }
            }
        }
        return 1;
    }
};