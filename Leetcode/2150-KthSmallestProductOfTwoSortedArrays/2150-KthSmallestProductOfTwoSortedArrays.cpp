// Last updated: 8/29/2026, 8:23:15 PM
class Solution {
public:
    int m=0,n=0;
    long long positiveCase(long long num, long long X, vector<int>& nums2){//find the last index such that num*nums2[index]<=X
        int low=0,high=n-1;
        int ans=-1;
        while(low<=high){
            int mid=low+(high-low)/2;
            if(num*nums2[mid]<=X){
                ans=mid;
                low=mid+1;
            }else{
                high=mid-1;
            }
        }
        return ans+1;
    }
    long long negativeCase(long long num, long long X, vector<int>& nums2){//find the last index such that num*nums2[index]>=X
        int low=0,high=n-1;
        int ans=-1;
        while(low<=high){
            int mid=low+(high-low)/2;
            if(num*nums2[mid]>X){
                ans=mid;
                low=mid+1;
            }else{
                high=mid-1;
            }
        }
        return n-1-ans;
    }
    long long zeroCase(long long X){
        if(X>=0){
            return n;
        }
        return 0;
    }
    int check(long long int X, vector<int>& nums1, vector<int>& nums2,long long k){
        long long count=0;
        for(int i=0;i<m;i++){
            if(nums1[i]>0){
                count+=positiveCase(1LL*nums1[i],X,nums2);
            }else if(nums1[i]<0){
                count+=negativeCase(1LL*nums1[i],X,nums2);
            }else{
                count+=zeroCase(X);
            }
            if(count>=k){
                return 1;
            }
        }
        return count>=k;
    }

    long long kthSmallestProduct(vector<int>& nums1, vector<int>& nums2, long long k) {
        m=nums1.size();
        n=nums2.size();
        long long firstA=1LL*nums1[0],lastA=1LL*nums1[m-1];
        long long firstB=1LL*nums2[0],lastB=1LL*nums2[n-1];
        long long low=min(min(firstA*firstB,firstA*lastB),min(lastA*firstB,lastA*lastB));
        long long high=max(max(firstA*firstB,firstA*lastB),max(lastA*firstB,lastA*lastB));
        if(m>n){
            swap(nums1,nums2);
            swap(m,n);
        }
        long long ans=0;
        while(low<=high){
            long long mid=low+(high-low)/2;
            int checkValue=check(mid,nums1,nums2,k);
            if(checkValue){
                ans=mid;
                high=mid-1;
            }else{
                low=mid+1;
            }
        }
        return ans;
    }
};