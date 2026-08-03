// Last updated: 8/3/2026, 9:53:56 PM
class Solution {
public:
    int n=0,m=0;
    int compatibility(vector<int>& s,vector<int>& m){
        int ans=0;
        for(int i=0;i<n;i++){
            ans+=(s[i]==m[i]);
        }
        return ans;
    }

    int maxCompatibilitySum(vector<vector<int>>& students, vector<vector<int>>& mentors) {
        //dp[mask]=maximum compatibility of all the students set to 1
        //dp[0]=0 as no students or mentors means no cost
        //dp[mask]=max(dp[previousState]+cost[previousToCurrent]) for all the states
        m=students.size();
        n=students[0].size();
        const int INF=1e9;
        vector<int> dp(1<<m,-INF);
        dp[0]=0;
        vector<vector<int>> score(m, vector<int>(m));
        for (int student = 0; student < m; student++) {
            for (int mentor = 0; mentor < m; mentor++) {
                score[student][mentor] =
                    compatibility(students[student], mentors[mentor]);
            }
        }
        int finalState=(1<<m)-1;
        for(int mask=1;mask<=finalState;mask++){//iterate over all masks increasingly
            int lastStudent=__builtin_popcount(mask)-1;
            for(int j=0;j<m;j++){//iterate over all students
                if(!(mask&(1<<j))){//skip if we cannot remove this student
                    continue;
                }
                int previousMask=(mask&~(1<<j));//remove this student
                dp[mask]=max(dp[mask],dp[previousMask]+score[lastStudent][j]);//calculate maximum with previous state + addition of last student/mentor
            }
        }
        return dp[finalState];
    }
};