// Last updated: 6/22/2026, 9:25:01 PM
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        //there are two sets of numbers - those which get + sign and those which get - sign
        //Let's denote the one with + sign with P, and those - sign as N
        //P+N=totalSum
        //P-N=target
        //2P=(totalSum+target)
        //P=(totalSum+target)/2
        //so problem reduces to finding a subset of sum=P
        int n=nums.size();
        int sum=0;
        for(int i=0;i<n;i++){
            sum+=nums[i];
        }
        int positiveSum=(sum+target)/2;
        if(positiveSum<0||(sum+target)%2){
            return 0;
        }
        if(target<-sum||target>sum){
            return 0;
        }
        vector<int> prev(positiveSum+1,0);
        prev[0]=1;
        for(int i=1;i<=n;i++){
            int element=nums[i-1];
            vector<int> cur(positiveSum+1,0);
            for(int j=0;j<=positiveSum;j++){
                cur[j]=prev[j];
                if(j-element>=0){
                    cur[j]+=prev[j-element];
                }
            }
            prev=cur;
        }
        return prev[positiveSum];
    }
};
//     int findTargetSumWays(vector<int>& nums, int target) {
//         //j can be negative
//         //dp[i][j]=number of different expression with first i numbers that sum up to j
//         //dp[i][j]=if(add +){dp[i][j]+=dp[i-1][j-num[i]]}else{do[i][j]+=dp[i-1][j+num[i]]}
//         //dp[0][j]=0
//         //dp[0][0]=1
//         //now since we cannot have negative indices we create an array of size 2n+1
//         //vector's index - j=dp'index
//         int n=nums.size();
//         int sum=0;
//         for(int i=0;i<n;i++){
//             sum+=nums[i];
//         }
//         if(target<-sum||sum<target){
//             return 0;
//         }
//         vector<int> prev(2*sum+1,0);
//         prev[sum]=1;
//         for(int i=1;i<=n;i++){
//             int element=nums[i-1];
//             vector<int> cur(2*sum+1,0);
//             for(int j=0;j<=2*sum;j++){
//                 if(j-element>=0){
//                     cur[j]+=prev[j-element];
//                 }
//                 if(j+element<=2*sum){
//                     cur[j]+=prev[j+element];
//                 }
//             }
//             prev=cur;
//         }
//         return prev[target+sum];
//     }
// };

/*
Input: nums = [1], target = 1
Output: 1
dp[0][-1]=0
dp[0][0]=1
dp[0][1]=0
dp[1][1]=dp[1-1][1-1]+dp[1-1][1+1]=dp[0][0]+dp[0][2]=1+0=1
*/

/*
Input: nums = [1,1,1], target = 3
Output: 1
dp[0][-3]=0
dp[0][-2]=0
dp[0][-1]=0
dp[0][0]=1
dp[0][1]=0
dp[0][2]=0
dp[0][3]=0
dp[3][3]=dp[3-1][3-1]+dp[3-1][3+1]=dp[2][2]+dp[2][4]=1+0=1
dp[2][2]=dp[2-1][2-1]+dp[2-1][2+1]=dp[1][1]+dp[1][3]=1+0=1
dp[1][1]=dp[1-1][1-1]+dp[1-1][1+1]=dp[0][0]+dp[0][2]=1+0=1
dp[1][3]=dp[1-1][3-1]+dp[1-1][3+1]=dp[0][2]+dp[0][4]=0+0=0
*/

/*
sum=3
[-3,-2,-1,0,1,2,3]
[0,  0, 0,1,0,0,0]
[0 , 1, 2,3,4,5,6]
[0 , 1, 2,3,4,5,6]

*/