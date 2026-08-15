// Last updated: 8/15/2026, 5:37:41 PM
class Solution {
public:
    int m=0,n=0;
    int dr[4]={-1,0,1,0};
    int dc[4]={0,1,0,-1};
    int isValid(int r,int c){
        return !(r<0||r>=m||c<0||c>=n);
    }
    int shortestPathAllKeys(vector<string>& grid) {
        //dp[mask][node]=current node with all the keys collected as shown in mask
        const int INF=1e9;
        m=grid.size();
        n=grid[0].size();
        int initialRow=0,initialColumn=0;
        vector<int> characterIndex;
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                char currentChar=grid[i][j];
                if(('a'<=currentChar)&&(currentChar<='z')){
                    characterIndex.push_back(currentChar-'a');
                }else if(currentChar=='@'){
                    initialRow=i;
                    initialColumn=j;
                }
            }
        }
        int finalMask=0;
        for(int i=0;i<characterIndex.size();i++){
            finalMask|=(1<<characterIndex[i]);
        }
        int initialMask=0;
        vector<vector<vector<int>>> distance(finalMask+1,vector<vector<int>>(m,vector<int>(n,INF)));
        queue<pair<int,pair<int,int>>> q;
        distance[initialMask][initialRow][initialColumn]=0;
        q.push(make_pair(initialMask,make_pair(initialRow,initialColumn)));
        while(!q.empty()){
            auto [mask,node]=q.front();
            q.pop();
            int nodeR=node.first;
            int nodeC=node.second;
            int dist=distance[mask][nodeR][nodeC];
            for(int i=0;i<4;i++){
                int neighR=nodeR+dr[i];
                int neighC=nodeC+dc[i];
                if(!isValid(neighR,neighC)){
                    continue;
                }
                char character=grid[neighR][neighC];
                if(character=='#'){
                    continue;
                }else if(('A'<=character)&&(character<='Z')){
                    int place=character-'A';
                    if(!(mask&(1<<place))){
                        continue;
                    }
                    if(distance[mask][neighR][neighC]<INF){
                        continue;
                    }
                    distance[mask][neighR][neighC]=1+dist;
                    q.push(make_pair(mask,make_pair(neighR,neighC)));
                }else if(('a'<=character)&&(character<='z')){
                    int place=character-'a';
                    int newMask=mask|(1<<place);
                    if(distance[newMask][neighR][neighC]<INF){
                        continue;
                    }
                    distance[newMask][neighR][neighC]=1+dist;
                    q.push(make_pair(newMask,make_pair(neighR,neighC)));
                }else{
                    if(distance[mask][neighR][neighC]<INF){
                        continue;
                    }
                    distance[mask][neighR][neighC]=1+dist;
                    q.push(make_pair(mask,make_pair(neighR,neighC)));
                }
            }
        }
        int ans=INF;
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                ans=min(ans,distance[finalMask][i][j]);
            }
        }
        return ans>=INF?-1:ans;
    }
};