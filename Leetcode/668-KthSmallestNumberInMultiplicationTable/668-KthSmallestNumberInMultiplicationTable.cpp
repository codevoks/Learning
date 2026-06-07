// Last updated: 6/7/2026, 11:25:50 PM
class Solution {
public:
    int check(int mid, int m, int n, int k){
        int i = m-1,j = 0;
        int count = 0;
        while((0<=i&&i<m)&&(0<=j&&j<n)){
            int ic=i+1, jc=j+1;
            if(ic*jc<=mid){
                count+=ic;
                j++;
            }else{
                i--;
            }
        }
        return count>=k;
    }
    int findKthNumber(int m, int n, int k) {
        long long low = 1*1;
        long long high = m*n;
        long long ans = high;
        while(low<=high){
            long long mid = low + (high-low)/2;
            if(check(mid,m,n,k)){
                ans = mid;
                high = mid-1;
            } else {
                low = mid+1;
            }
        }
        return ans;
    }
};