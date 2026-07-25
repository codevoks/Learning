// Last updated: 7/25/2026, 10:16:10 PM
class Solution {
public:
    static bool compare(array<int,3>& job1,array<int,3>& job2){
        return job1[1]<job2[1];
    }
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        //dp[i]=maximum profit using jobs till i
        //dp[i]=max(dp[i-1],Profit till last compatible Job + Profit[i]);
        //compatible <=> end[compatible job]<=start[current job]
        //now we have start everytime so we need efficient searching for end time
        int n=startTime.size();
        vector<array<int,3>> jobs;
        for(int i=0;i<n;i++){
            jobs.push_back({startTime[i],endTime[i],profit[i]});
        }
        sort(jobs.begin(),jobs.end(),compare);
        vector<int> dp(n);
        dp[0]=jobs[0][2];
        for(int i=1;i<n;i++){
            int lastValidIndex=-1;
            int l=0,h=i-1;
            while(l<=h){
                int mid=l+(h-l)/2;
                if(jobs[mid][1]<=jobs[i][0]){
                    lastValidIndex=mid;
                    l=mid+1;
                }else{
                    h=mid-1;
                }
            }
            int take=jobs[i][2];
            if(lastValidIndex!=-1){
                take+=dp[lastValidIndex];
            }
            dp[i]=max(dp[i-1],take);
        }
        return dp[n-1];
    }
};