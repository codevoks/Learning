// Last updated: 6/7/2026, 11:28:02 PM
class Solution {
public:
    int f(int i,int j,string &s,string &p)
    {
        if(i<0&&j<0)
        {
            return 1;
        }
        if(i>=0&&j<0)
        {
            return 0;
        }
        if(i<0&&j>=0)
        {
            if(p[j]=='*')
            {
                return f(i,j-2,s,p);
            }
            return 0;
        }
       
        if(p[j]==s[i]||p[j]=='.')
        {
            return f(i-1,j-1,s,p);
        }
        bool cond1=false,cond2=false;
        if(p[j]=='*')
        {
            //if(i==1)return 1;
            //cond1 we take 0 repetition of preceding
            cond1 = f(i,j-2,s,p);
            //cond2 we take 1 repetition of preceding
           cond2 = ((p[j-1]=='.'||p[j-1]==s[i]))&&f(i-1,j,s,p);
            //cond2 =  f(i-1,j,s,p);
        }
        return cond1||cond2;
    }
    bool isMatch(string s, string p) 
    {
        int i = s.size();
        int j = p.size();
        return f(i-1,j-1,s,p);
    }
};
