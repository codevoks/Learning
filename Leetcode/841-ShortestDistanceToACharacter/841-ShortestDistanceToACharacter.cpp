// Last updated: 6/7/2026, 11:25:34 PM
class Solution {
public:
    vector<int> shortestToChar(string s, char c) {
        int n = s.length();
        vector<int> ans(n,INT_MAX);
        vector<int> store;
        for(int i= 0;i<s.length();i++)
        {
            if(s[i]==c)
            {
                store.push_back(i);
            }
        }
        for(int i = 0;i<n;i++)
        {
            if(s[i]==c)
            {
                ans[i]=0;
                continue;
            }
            /*
            int f = i+1;
            int fa = INT_MAX;
            while(f<=n-1)
            {
                if(s[f]==c)
                {
                    fa = min(fa,abs(f-i));
                    break;
                }
                f++;
            }
            int b = i-1;
            int ba = INT_MAX;
            while(0<=b)
            {
                if(s[b]==c)
                {
                    ba = min(ba,abs(b-i));
                    break;
                }
                b--;
            }*/
            //last occurence in previous array
            int s = 0,e = store.size()-1;
            int ansb,ansf;
            ans[i]=INT_MAX;
            if(store[0]<i)
            {
                while(s<=e)
                {
                    int m  = s + (e-s)/2;
                    if(store[m]==i)
                    {
                        ansb = store[m];
                        break;
                    }
                    else if(store[m]<i)
                    {
                        ansb = store[m];
                        s = m+1;
                    }
                    else
                    {
                        e = m-1;
                    }
                }
                ans[i]=min(ans[i],abs(i-ansb));
            }
            //first occurenci nnext array
            s=0,e = store.size()-1;
            if(store[store.size()-1]>i)
            {
                while(s<=e)
                {
                    int m = s + (e-s)/2;
                    if(store[m]==i)
                    {
                        ansf = store[m];
                        break;
                    }
                    else if(store[m]>i)
                    {
                        ansf = store[m];
                        e = e-1;
                    }
                    else
                    {
                        s = m+1;
                    }
                }
                ans[i]=min(ans[i],abs(i-ansf));
            }
        }
        return ans;
    }
};