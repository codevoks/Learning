// Last updated: 7/10/2026, 10:47:57 PM
class Solution {
public:
    int n=0;
    int check(int mid, vector<int>& bloomDay, int m, int k){
        int flowersTaken=0;
        int bouquets=0;
        for(int i=0;i<n;i++){
            if(bloomDay[i]<=mid){
                flowersTaken++;
                if(flowersTaken==k){
                    bouquets++;
                    flowersTaken=0;
                }
            }else{
                flowersTaken=0;
            }
        }
        return bouquets>=m;
    }
    int minDays(vector<int>& bloomDay, int m, int k) {
        n=bloomDay.size();
        int lb=bloomDay[0];
        int ub=bloomDay[0];
        for(int i=1;i<n;i++){
            lb=min(lb,bloomDay[i]);
            ub=max(ub,bloomDay[i]);
        }
        int ans=-1;
        while(lb<=ub){
            int mid=lb+(ub-lb)/2;
            if(check(mid,bloomDay,m,k)){
                ans=mid;
                ub=mid-1;
            }else{
                lb=mid+1;
            }
        }
        return ans;
    }
};