// Last updated: 6/7/2026, 11:27:01 PM
class Solution {
public:
    int m,n;
    int dr[4]={-1,0,1,0};
    int dc[4]={0,1,0,-1};
    int isValid(int r,int c){
        return !(r<0||r>=m||c<0||c>=n);
    }
    void dfs(int r,int c, vector<vector<char>>& board){
        board[r][c]='#';
        for(int i=0;i<4;i++){
            auto [nr,nc] = make_pair(r+dr[i],c+dc[i]);
            if(isValid(nr,nc)&&board[nr][nc]=='O'){
                dfs(nr,nc,board);
            }
        }
    }
    void solve(vector<vector<char>>& board) {
        m=board.size();
        n=board[0].size();
        vector<vector<int>> visited(m,vector<int> (n,0));
        int borderRows[2]={0,m-1};
        int borderColumns[2]={0,n-1};
        for(int i=0;i<2;i++){
            for(int j=0;j<n;j++){
                if(board[borderRows[i]][j]=='O'){
                    dfs(borderRows[i],j,board);
                }
            }
        }
        for(int i=0;i<2;i++){
            for(int j=0;j<m;j++){
                if(board[j][borderColumns[i]]=='O'){
                    dfs(j,borderColumns[i],board);
                }
            }
        }
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(board[i][j]=='O'){
                    board[i][j]='X';
                }else if(board[i][j]=='#'){
                    board[i][j]='O';
                }
            }
        }
    }
};