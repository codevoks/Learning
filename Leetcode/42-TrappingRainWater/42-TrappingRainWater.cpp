// Last updated: 6/7/2026, 11:27:47 PM
class Solution {
public:

    int pre_val(int ind,vector<int>& height,vector<int>& pre)
    {
        int n = height.size();
        if(pre[ind]<0)
        {
            return 0;
        }
        return height[pre[ind]];
    }

    int post_val(int ind,vector<int>& height,vector<int> &post)
    {
        int n = height.size();
        if(post[ind]>n-1)
        {
            return 0;
        }
        return height[post[ind]];
    }

    int trap(vector<int>& height) 
    {
        int n = height.size();
        int ans = 0;
        stack<int> st;
        vector<int> prev(n);
        vector<int> next(n);
        for(int i = 0;i<n;i++)
        {
            int cur = height[i];
            while(!st.empty()&&cur>height[st.top()])
            {
                st.pop();
            }
            if(st.empty())
            {
                prev[i]=-1;
                st.push(i);
            }
            else
            {
                prev[i]=st.top();
            }
        }
        while(!st.empty())
        {
            st.pop();
        }
        for(int i =n-1;i>=0;i--)
        {
            int cur =height[i];
            while(!st.empty()&&cur>height[st.top()])
            {
                st.pop();
            }
            if(st.empty())
            {
                next[i]=n;
                st.push(i);
            }
            else
            {
                next[i]=st.top();
            }
        }
        for(auto it:prev)
        {
            cout<<it<<" ";
        }
        cout<<"\n";
        for(auto it:next)
        {
            cout<<it<<" ";
        }
        cout<<"\n";
        for(int i = 1;i<n-1;i++)
        {
            int pr = pre_val(i,height,prev);
            int po = post_val(i,height,next);
            int mini = min(pr,po);
            ans+=max((mini-height[i]),0);
        }
        return ans;
    }
};