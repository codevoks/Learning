// Last updated: 9/13/2026, 9:01:32 AM
class Solution {
public:
    int atMostNGivenDigitSet(vector<string>& digits, int n) {
        string number=to_string(n);
        int len=number.size();

        vector<vector<vector<int>>> dp(len+1,vector<vector<int>>(2,vector<int>(2)));
        dp[0][1][0]=1;
        dp[0][0][0]=0;

        for(int pos=1;pos<=len;pos++){
            for(int prevTight=0;prevTight<=1;prevTight++){
                for(int prevStarted=0;prevStarted<=1;prevStarted++){
                    //first thing we need is the digit under consideration
                    int currentDigitOfN=number[pos-1]-'0';
                    //and the limit
                    int limit=prevTight?currentDigitOfN:9;
                    //if we have not started yet and we don't want to start either, then we can only add 0
                    if(prevStarted==0){
                        int digit=0;
                        // in our case below two lines are always true
                        // int currentStarted=0;
                        // int currentTight=0;
                        int currentTight=prevTight && (digit==currentDigitOfN);
                        int currentStarted=prevStarted || (digit!=0);
                        dp[pos][currentTight][currentStarted]+=dp[pos-1][prevTight][prevStarted];
                    }
                    //now for case when we want to start
                    //first find the limit
                    for(int i=0;i<digits.size();i++){
                        int currentDigit=digits[i][0]-'0';
                        if(currentDigit>limit){
                            break;
                        }
                        int currentTight=prevTight && (currentDigit==currentDigitOfN);
                        int currentStarted=prevStarted || (currentDigit!=0);
                        dp[pos][currentTight][currentStarted]+=dp[pos-1][prevTight][prevStarted];
                    }
                }
            }
        }
        return dp[len][1][1]+dp[len][0][1];
    }
};