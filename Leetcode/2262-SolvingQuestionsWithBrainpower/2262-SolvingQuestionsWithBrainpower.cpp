// Last updated: 6/13/2026, 2:09:06 PM
class Solution {
public:
    long long mostPoints(vector<vector<int>>& questions) {
        //dp[i]=maximum score till index i
        //but this state is not suffiecient as for dp[i] we don't know which dp[j] j's(<i) to use
        //we need to know which problem we solved last to have a choice on i
        //dp[i]=maximum points we can score if we start from i seems more natural as it previous one left us in indicision
        int n=questions.size();
        if(n==1){
            return questions[n-1][0];
        }
        vector<long long int> dp(n);
        dp[n-1]=questions[n-1][0];
        for(int i=n-2;i>=0;i--){
            long long int solve=questions[i][0]+((i+questions[i][1]+1<=n-1)?dp[i+questions[i][1]+1]:0);
            long long int skip=(i+1<=n-1)?dp[i+1]:0;
            dp[i]=max(solve,skip);
        }
        return dp[0];
    }
};