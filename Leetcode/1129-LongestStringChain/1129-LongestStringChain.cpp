// Last updated: 7/22/2026, 9:24:09 PM
class Solution {
public:
    static int compare(const string& a, const string& b){
        return a.size()<b.size();
    }
    int isPredecessor(string a,string b){
        int l1=a.size();
        int l2=b.size();
        if(l1+1!=l2){
            return 0;
        }
        int i=0,j=0;
        while(i<l1&&j<l2){
            if(a[i]==b[j]){
                i++;
                j++;
            }else{
                j++;
            }
        }
        return i==l1;
    }
    int longestStrChain(vector<string>& words) {
        //dp[i] - length of lis ending at i
        sort(words.begin(),words.end(),compare);
        int n=words.size();
        vector<int> dp(n,1);
        for(int i=0;i<n;i++){
            for(int j=0;j<i;j++){
                if(isPredecessor(words[j],words[i])){
                    if(dp[j]+1>dp[i]){
                        dp[i]=dp[j]+1;
                    }
                }
            }
        }
        int ans=0;
        for(int i=0;i<n;i++){
            ans=max(ans,dp[i]);
        }
        return ans;
    }
};