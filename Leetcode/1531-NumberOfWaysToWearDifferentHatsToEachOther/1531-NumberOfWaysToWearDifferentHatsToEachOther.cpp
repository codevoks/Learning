// Last updated: 8/15/2026, 5:37:04 PM
class Solution {
public:
    int numberWays(vector<vector<int>>& hats) {
        //since numbers of hats is 40 we cannot create a mask for it
        //dp[mask][h]=numbers of ways to assign first h hats to everyone set in mask
        //dp[0][0]=1
        const int MOD=1e9+7;
        int n=hats.size();
        int hatsCount=40;
        vector<vector<int>> hatToPeople(hatsCount,vector<int>());
        for(int i=0;i<n;i++){
            for(int j=0;j<hats[i].size();j++){
                hatToPeople[hats[i][j]-1].push_back(i);
            }
        }
        int initialMask=1;
        int finalMask=(1<<n)-1;
        vector<vector<int>> dp(finalMask+1,vector<int>(hatsCount+1,0));
        dp[0][0]=1;
        for(int hatsUsed=1;hatsUsed<=hatsCount;hatsUsed++){
            int hatIndex=hatsUsed-1;
            for(int mask=0;mask<=finalMask;mask++){
                if(hatsUsed<__builtin_popcount(mask)){
                    continue;
                }
                //skipping current hat
                dp[mask][hatsUsed]=dp[mask][hatsUsed-1];
                for(int i=0;i<hatToPeople[hatIndex].size();i++){
                    //skip those people that are already present in the mask
                    if(!(mask&(1<<hatToPeople[hatIndex][i]))){
                        continue;
                    }
                    int previousMask=mask&~(1<<hatToPeople[hatIndex][i]);
                    int previousHatsUsed=hatsUsed-1;
                    dp[mask][hatsUsed]+=(dp[previousMask][previousHatsUsed])%MOD;
                    dp[mask][hatsUsed]%=MOD;
                }
            }
        }
        return dp[finalMask][hatsCount];
    }
};