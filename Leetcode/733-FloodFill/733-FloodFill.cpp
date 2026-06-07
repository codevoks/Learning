// Last updated: 6/7/2026, 11:25:45 PM
class Solution {
public:
    int m,n;
    int originalColor, newColor;
    int dr[4]={-1,0,1,0};
    int dc[4]={0,1,0,-1};

    int isValid(int r, int c){
        return !(r<0 || r>=m || c<0 || c>=n);
    }

    void dfs(int r,int c ,vector<vector<int>>& image){
        image[r][c]=newColor;
        for(int i=0;i<4;i++){
            int nr = r+dr[i];
            int nc = c+dc[i];
            if(isValid(nr,nc) && image[nr][nc]==originalColor){
                dfs(nr,nc,image);
            }
        }
    }

    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
        m=image.size();
        n=image[0].size();
        originalColor = image[sr][sc];
        newColor = color;
        if(newColor!=originalColor){
            dfs(sr,sc,image);
        }
        return image;
    }
};