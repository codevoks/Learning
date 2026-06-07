// Last updated: 6/7/2026, 11:26:12 PM
class Solution {
public:
    int check(long long int mid,vector<vector<int>>& matrix, int k, int n){
        int count = 0;
        for(int i =0;i<n;i++){
            count+=(upper_bound(matrix[i].begin(),matrix[i].end(),mid)-matrix[i].begin());
        }
        return count>=k;
    }

    int checkEfficient(long long int mid,vector<vector<int>>& matrix, int k, int n){
        int count = 0;
        int i = n-1,j=0;
        while((0<=i&&i<n)&&(0<=j&&j<n)){
            if(mid>=matrix[i][j]){
                count+=(i+1);
                j++;
            } else {
                i--;
            }
        }
        return count>=k;
    }

    int kthSmallest(vector<vector<int>>& matrix, int k) {
        int n = matrix.size();
        int ans = matrix[n-1][n-1];
        long long int low = matrix[0][0];
        long long int high = matrix[n-1][n-1];
        while(low<=high){
            long long int mid = low + (high-low)/2;
            if(checkEfficient(mid,matrix,k,n)){
                ans = mid;
                high = mid-1;
            }else{
                low = mid+1;
            }
        }
        return ans;
    }
};