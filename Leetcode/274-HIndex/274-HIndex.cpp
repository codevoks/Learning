// Last updated: 6/7/2026, 11:26:20 PM
class Solution {
public:

    int check(vector<int>& citations,int mid)
    {
        int n = citations.size();
        int count = 0;
        for(int i = 0;i<n;i++)
        {
            if(citations[i]>=mid)
            {
                count++;
            }
        }
        return count>=mid;
    }

    int hIndex(vector<int>& citations) {
        int n = citations.size();
        //answer lies in the range 0 to n also we have a monotone space so apply BS
        int ans = 0;
        int low=0,high=n;
        while(low<=high)
        {
            int mid = low + (high-low)/2;
            if(check(citations,mid))
            {
                ans  = mid;
                low = mid +1;
            }
            else
            {
                high=mid-1;
            }
        }
        return ans;
    }
};