// Last updated: 9/13/2026, 9:00:48 AM
class Solution {
public:
    int n=0;
    int check(int mid,vector<int>& weights, int days){
        int daysTaken=1;
        long long int weightTaken=0;
        for(int i=0;i<n;i++){
            if(weights[i]>mid){
                return 0;
            }
            if(weightTaken+weights[i]<=mid){
                weightTaken+=weights[i];
            }else{
                weightTaken=weights[i];
                daysTaken++;
            }
        }
        return daysTaken<=days;
    }
    int shipWithinDays(vector<int>& weights, int days) {
        n=weights.size();
        int lb=weights[0];
        int ub=weights[0];
        for(int i=1;i<n;i++){
            lb=min(lb,weights[i]);
            ub+=weights[i];
        }
        long long int ans=ub;
        while(lb<=ub){
            int mid=lb+(ub-lb)/2;
            if(check(mid,weights,days)){
                ans=mid;
                ub=mid-1;
            }else{
                lb=mid+1;
            }
        }
        return ans;
    }
};