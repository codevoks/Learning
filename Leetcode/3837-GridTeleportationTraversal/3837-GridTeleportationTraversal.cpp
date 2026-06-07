// Last updated: 6/7/2026, 11:24:37 PM
class Solution {
public:
    int m,n;
    int dr[4]={-1,0,1,0};
    int dc[4]={0,1,0,-1};

    int isValid(int r,int c){
        return !(r<0 || r>=m || c<0 || c>=n);
    }

    int minMoves(vector<string>& matrix) {
        unordered_map<char,vector<pair<int,int>>> portals;
        m = matrix.size();
        n = matrix[0].size();
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if('A'<=matrix[i][j]&&matrix[i][j]<='Z'){
                    portals[(char)matrix[i][j]].push_back({i,j});
                }
            }
        }
        vector<vector<int>> distance(m,vector<int>(n,1e9));
        deque <pair<int,int>> dq;
        dq.push_front({0,0});
        distance[0][0]=0;
        while(!dq.empty()){
            auto [r,c] = dq.front();
            dq.pop_front();
            if('A'<=matrix[r][c]&&matrix[r][c]<='Z'){
                for(auto [pr,pc]: portals[matrix[r][c]]){
                    if(distance[r][c]<distance[pr][pc]){
                        distance[pr][pc] = distance[r][c];
                        dq.push_front({pr,pc});
                    }
                }
                portals[matrix[r][c]].clear();
            }
            for(int i=0;i<4;i++){
                int weight = 1;
                if(isValid(r+dr[i],c+dc[i])&&matrix[r+dr[i]][c+dc[i]]!='#'&&distance[r][c]+weight<distance[r+dr[i]][c+dc[i]]){
                    distance[r+dr[i]][c+dc[i]]=distance[r][c]+weight;
                    if(weight){
                        dq.push_back({r+dr[i],c+dc[i]});
                    }
                }
            }
        }
        return distance[m-1][n-1]>=1e9?-1:distance[m-1][n-1];
    }
};