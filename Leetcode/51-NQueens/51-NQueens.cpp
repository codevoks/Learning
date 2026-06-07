// Last updated: 6/7/2026, 11:27:44 PM
class Solution {
public:
    
    bool valid(int row,int column,vector<string> &board,int n)
    {
        int r = row;
        int c = column;
        while(r>=0&&c>=0)
        {
            if(board[r][c]=='Q')
            {
                return false;
            }
            r--;
            c--;
        }
        r=row;
        c=column;
        while(c>=0)
        {
            if(board[r][c]=='Q')
            {
                return false;
            }
            c--;
        }
        r=row;
        c=column;
        while(r<=n-1&&c>=0)
        {
            if(board[r][c]=='Q')
            {
                return false;
            }
            r++;
            c--;
        }
        return true;
    }
    
    void fill(int row,int column,vector<string> &board,vector<vector<string>> &ans,int n)
    {
        if(column==n)
        {
            ans.push_back(board);
            return;
        }
        for(int i=0;i<n;i++)
        {
            if(valid(i,column,board,n))
            {
                board[i][column]='Q';
                fill(i,column+1,board,ans,n);
                board[i][column]='.';
            }
        }
    }
    
    vector<vector<string>> solveNQueens(int n) 
    {
        vector<vector<string>> ans;
        vector<string> board(n);
        for(int i = 0;i<n;i++)
        {
            string s(n,'.');
            board[i]=s;
        }
        fill(0,0,board,ans,n);
        return ans;
    }
};