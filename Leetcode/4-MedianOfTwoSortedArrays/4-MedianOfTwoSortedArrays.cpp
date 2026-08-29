// Last updated: 8/29/2026, 8:27:02 PM
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        const int INF=1e9;
        int m=nums1.size();
        int n=nums2.size();
        int total=m+n;
        int leftSize=(total+1)/2;
        //now let's analise the size of cutA (element of nums1 in left partition of size leftSize)
        //cutA+cutB=leftSize
        //so when cutA is lowest, cutB is its highest
        //so high can cutB get? It can get minimum(n,leftSize)
        //so cutA lowest = leftSize-minimum(n,leftParition)
        int low=leftSize-min(n,leftSize);
        //how high can cutA get? It can get minimum(m,leftSize)
        int high=min(m,leftSize);
        int LA=-INF,LB=-INF,RA=INF,RB=INF;
        int ans=0;
        while(low<=high){
            int mid=low+(high-low)/2;
            int cutA=mid;
            int cutB=leftSize-mid;
            LA=(cutA==0)?-INF:nums1[cutA-1];
            LB=(cutB==0)?-INF:nums2[cutB-1];
            RA=(m-cutA==0)?INF:nums1[cutA];
            RB=(n-cutB==0)?INF:nums2[cutB];
            if(LA>RB){
                high=mid-1;
            }else if(LB>RA){
                low=mid+1;
            }else{
                ans=mid;
                break;
            }
        }
        double median=0;
        if(total%2){
            median=max(LA,LB);
        }else{
            median=(max(LA,LB)+min(RA,RB))/2.0;
        }
        return median;
    }
};