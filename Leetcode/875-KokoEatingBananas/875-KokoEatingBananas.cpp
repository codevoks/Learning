// Last updated: 9/13/2026, 9:01:37 AM
class Solution {
public:
    int check(long long int mid,vector<int>& piles, int h){
        long long int hours=0;
        for(auto pile:piles){
            hours+=(pile/mid);
            if(pile%mid){
                hours++;
            }
        }
        return hours<=h;
    }
    int minEatingSpeed(vector<int>& piles, int h) {
        int n=piles.size();
        long long int lb=1;
        long long int ub=piles[0];
        for(int i=0;i<n;i++){
            ub=max(ub,1LL*piles[i]);
        }
        long long int ans=-1;
        while(lb<=ub){
            long long int mid=lb+(ub-lb)/2;
            if(check(mid,piles,h)){
                ans=mid;
                ub=mid-1;
            }else{
                lb=mid+1;
            }
        }
        return ans;
    }
};