// Last updated: 6/7/2026, 11:25:15 PM
class Solution {
public:
    int check(vector<int>& weights,long long X,int days){
        if(weights.size()<1){
            return true;
        }
        int daysConsumed = 1;
        long long currentWeight = weights[0];
        for(int i = 1;i<weights.size();i++){
            if(currentWeight + weights[i] <=X){
                currentWeight+=weights[i];
            }else if(weights[i]<=X){
                currentWeight = weights[i];
                daysConsumed++;
            }
        }
        return daysConsumed<=days;
    }

    int shipWithinDays(vector<int>& weights, int days) {
        long long totalWeight= 0,maximumWeight = 0;
        for(auto weight: weights){
            totalWeight+=weight;
            maximumWeight = max(maximumWeight,weight*1LL);
        }
        long long l = maximumWeight;
        long long r = totalWeight;
        long long ans = totalWeight;
        while(l<=r){
            long long mid = l + (r-l)/2;
            if(check(weights,mid,days)){
                ans = mid;
                r=mid-1;
            }else{
                l=mid+1;
            }
        }
        return ans;
    }
};