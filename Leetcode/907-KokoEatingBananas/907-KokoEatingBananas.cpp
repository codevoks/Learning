// Last updated: 6/7/2026, 11:25:30 PM
class Solution {
public:
    long findTotalBananas(vector<int>& piles){
        long sum=0;
        for(auto it: piles){
            sum+=it;
        }
        return sum;
    }

    int check(vector<int>& piles, int h, int k){
        long hours = 0;
        for(auto it: piles){
            hours+=(ceil((it*1.0)/k));
        }
        return hours <= h;
    }

    int minEatingSpeed(vector<int>& piles, int h) {
        int n = piles.size();
        long totalBananas = findTotalBananas(piles);
        int l = 1;
        int r = *max_element(piles.begin(), piles.end());
        int ans = -1;
        cout<<" totalBananas=> "<<totalBananas<<"\n";
        cout<<" h=> "<<h<<"\n";
        while(l<=r){
            int mid = l + (r-l)/2;
            if(check(piles,h,mid)){
                ans=mid;
                r=mid-1;
            }else{
                l=mid+1;
            }
        }
        return ans;
    }
};