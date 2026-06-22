// Last updated: 6/22/2026, 9:24:59 PM
class Solution {
public:
    pair<int,int> getZerosOnes(string s){
        int zeros,ones;
        zeros=ones=0;
        for(int i=0;i<s.size();i++){
            if(s[i]-'0'){
                ones++;
            }else{
                zeros++;
            }
        }
        return make_pair(zeros,ones);
    }
    int findMaxForm(vector<string>& strs, int m, int n) {
        //dp[i][j][k]=largest subset using first i entries that has at most j #0 and atmost k #1
        //dp[i][j][k]=max of all 3 cases if(not take){dp[i-1][j][k]}if(take){1+dp[i-1][j-numberOf0s][k-numberOf1s]}
        //dp[0][j][k]=0, for all j and k
        //dp[i][0][0]=0 for all i
        int N=strs.size();
        int zerosSum,onesSum;
        zerosSum=onesSum=0;
        vector<pair<int,int>> zerosOnes;
        for(int i=0;i<N;i++){
            pair<int,int> element=getZerosOnes(strs[i]);
            zerosOnes.push_back(element);
        }
        vector<vector<unsigned int>> prev(m+1,vector<unsigned int>(n+1,0));
        for(int i=1;i<=N;i++){
            pair<int,int> element=zerosOnes[i-1];
            int zeros=element.first;
            int ones=element.second;
            vector<vector<unsigned int>> cur(m+1,vector<unsigned int>(n+1,0));
            for(int i=0;i<=m;i++){
                for(int j=0;j<=n;j++){
                    cur[i][j]=prev[i][j];
                    if(i-zeros>=0&&j-ones>=0){
                        cur[i][j]=max(cur[i][j],1+prev[i-zeros][j-ones]);
                    }
                }
            }
            prev=cur;
        }
        return prev[m][n];
    }
};