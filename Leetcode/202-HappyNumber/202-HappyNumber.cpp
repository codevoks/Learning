// Last updated: 6/7/2026, 11:26:34 PM
class Solution {
public:
    int fun(int x)
    {
        int sum = 0;
        while(x>0)
        {
            int digit = (x%10);
            sum+=(digit*digit);
            x/=10;
            cout<<" sum == "<<sum<<"\n";
        }
        return sum;
    }
    bool isHappy(int n) {
        int x = n;
        map<int,int> encounter;
        while(encounter[x]==0&&x!=1)
        {
            cout<<" x at start = "<<x<<"\n";
            int y= fun(x);
            encounter[x]++;
            x=y;
            cout<<" x at end = "<<x<<"\n";
        }
        return x==1;
    }
};