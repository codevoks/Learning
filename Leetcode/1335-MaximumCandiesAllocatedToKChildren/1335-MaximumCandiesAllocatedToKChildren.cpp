// Last updated: 6/7/2026, 11:25:08 PM
using lli = long long;
#define INF 1e18
class Solution {
public:

    lli check(lli mid,vector<int>& candies, long long k,lli n)
    {
        //we iterate through entire array se how many chunks of mid we can find
        lli count = 0;
        for(lli i =0;i<n;i++)
        {
            if(candies[i]>=mid)
            {
                count+=(candies[i]/mid);
            }
        }
        return count>=k;
    }

    int maximumCandies(vector<int>& candies, long long k) {
        //find the size of array
        lli n = candies.size();
        //now use binary search on answer
        //low = 0, not possible
        //high = max_i(candies(i)), maximum answer we can have

        lli low = 1;
        lli high = -INF;
        for(lli i =0;i<n;i++)
        {
            high = max(high,1LL*candies[i]);
        }
        lli ans = 0;
        while(low<=high)
        {
            lli mid = low + (high-low)/2;
            if(check(mid,candies,k,n)==1) // check if we divide the piles so that we have each child get candies pile of size mid, also if we can have the size of this we can any value less than it
            {
                ans = mid;
                low = mid+1;
            }
            else
            {
                high = mid-1;
            }
        }
        return ans;
    }
};