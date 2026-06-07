// Last updated: 6/7/2026, 11:24:39 PM
class Solution {
public:
    int check(int r,int c,vector<vector<int>>& image, int threshold)
    {
        int flag=1;
        for(int i=0;i<3;i++)
        {
            for(int j=0;j<2;j++)
            {
                if(abs(image[r+i][c+j]-image[r+i][c+j+1])>threshold)
                {
                    flag=0;
                }
            }
        }
        for(int i=0;i<3;i++)
        {
            for(int j=0;j<2;j++)
            {
                if(abs(image[r+j][c+i]-image[r+j+1][c+i])>threshold)
                {
                    flag=0;
                }
            }
        }
        return flag;
    }
    vector<vector<int>> resultGrid(vector<vector<int>>& image, int threshold) {
        int n = image.size();
        int m = image[0].size();
        vector<vector<int>> sum(n,vector<int>(m,0));    //stores the total sum of averages
        vector<vector<int>> count(n,vector<int>(m,0));  //stores the number of regions a particular cell belongs to
        vector<vector<int>> ans(n,vector<int>(m,0));
        for(int i = 0;i<=n-3;i++)
        {
            for(int j=0;j<=m-3;j++)
            {
                if(check(i,j,image,threshold))
                {
                    //increase count of entire 3X3 matrix by 1
                    //calculate average and add to sum
                    int total = 0;
                    for(int p=i;p<i+3;p++)
                    {
                        for(int q=j;q<j+3;q++)
                        {
                            count[p][q]++;
                            total+=image[p][q];
                        }
                    }
                    int average = total/9;
                    for(int p=i;p<i+3;p++)
                    {
                        for(int q=j;q<j+3;q++)
                        {
                            sum[p][q]+=average;
                        }
                    }
                }
            }
        }
        for(int i =0;i<n;i++)
        {
            for(int j=0;j<m;j++)
            {
                if(count[i][j]==0)
                {
                    ans[i][j]=image[i][j];
                }
                else
                {
                    ans[i][j]=sum[i][j]/count[i][j];
                }
            }
        }
        return ans;
    }
};