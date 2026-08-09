// Last updated: 8/9/2026, 2:42:36 PM
class Solution {
public:
    int getOverlap(string word1, string word2){
        int n1=word1.size();
        int n2=word2.size();
        int mx=min(n1,n2);
        int ans=0;
        for(int i=0;i<mx;i++){
            string suffix=word1.substr(n1-1-i,i+1);
            string prefix=word2.substr(0,i+1);
            if(suffix==prefix){
                ans=max(ans,(int)suffix.length());
            }
        }
        return ans;
    }
    string shortestSuperstring(vector<string>& words) {
        int n=words.size();
        vector<vector<int>> overlap(n,vector<int>(n,0));
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(i!=j){
                    overlap[i][j]=getOverlap(words[i],words[j]);
                }
            }
        }
        const int INF=1e9;
        int finalMask=(1<<n)-1;
        vector<vector<int>> parent(finalMask+1,vector<int>(n,-1));
        vector<vector<int>> dp(finalMask+1,vector<int>(n,INF));
        for(int i=0;i<n;i++){
            dp[1<<i][i]=words[i].size();
        }
        for(int mask=1;mask<=finalMask;mask++){
            for(int current=0;current<n;current++){
                //current should be present in current mask
                if(!(mask&(1<<current))){
                    continue;
                }
                int previousMask=mask&~(1<<current);
                for(int previous=0;previous<n;previous++){
                    //previous must be in previousMask
                    if(!(previousMask&(1<<previous))){
                        continue;
                    }
                    int candidate=dp[previousMask][previous]+words[current].size()-overlap[previous][current];
                    if(candidate<dp[mask][current]){
                        dp[mask][current]=candidate;
                        parent[mask][current]=previous;
                    }
                }
            }
        }
        int ansLength=INF;
        int last=-1;
        for(int i=0;i<n;i++){
            if(dp[finalMask][i]<ansLength){
                ansLength=dp[finalMask][i];
                last=i;
            }
        }
        int current=last;
        int mask=finalMask;
        vector<int> order;
        while(current!=-1){
            order.push_back(current);
            int previous=parent[mask][current];
            mask=mask&~(1<<current);
            current=previous;
        }
        reverse(order.begin(),order.end());
        string ans=words[order[0]];
        for(int i=1;i<n;i++){
            int previousIndex=order[i-1];
            int currentIndex=order[i];
            ans+=words[currentIndex].substr(overlap[previousIndex][currentIndex]);
        }
        return ans;
    }
};