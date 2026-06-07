// Last updated: 6/7/2026, 11:27:32 PM
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();
        vector<int> pse(n);
        vector<int> nse(n);
        stack<int> s,t;
        for(int i=0;i<n;i++)
        {
            while(!s.empty()&&heights[s.top()]>=heights[i])
            {
                s.pop();
            }
            if(s.empty())
            {
                pse[i]=0;
            }
            else
            {
                pse[i]=s.top()+1;
            }
            s.push(i);
        }
        for(int i = n-1;i>=0;i--)
        {
            while(!t.empty()&&heights[t.top()]>=heights[i])
            {
                t.pop();
            }
            if(t.empty())
            {
                nse[i]=n-1;
            }
            else
            {
                nse[i]=t.top()-1;
            }
            t.push(i);
        }
        int ans = 0;
        for(int i = 0;i<n;i++)
        {
            ans = max(ans,heights[i]*(nse[i]-pse[i]+1));
        }
        return ans;
    }
};