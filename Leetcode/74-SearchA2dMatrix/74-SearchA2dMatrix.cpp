// Last updated: 6/7/2026, 11:27:35 PM
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int r = matrix.size();
        int c = matrix[0].size();
        int s = 0;
        int e = r*c-1;
        while(s<=e)
        {
            int mid = s + (e-s)/2;
            int i = mid/c;
            int j = mid%c;
            if(matrix[i][j]==target)
            {
                return 1;
            }
            else if(matrix[i][j]<target)
            {
                s =mid+1;
            }
            else
            {
                e = mid-1;
            }
        }
        return 0;
    }
};