// Last updated: 6/7/2026, 11:26:22 PM
class Solution {
public:

    int value(int x)
    {
        if(x==0)
        {
            return 1;
        }
        return x;
    }

    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> pre(n+2,1);
        for(int i =1;i<=n;i++)
        {
            pre[i]=pre[i-1]*nums[i-1];
        }
        pre[n+1]=pre[n];
        for(auto it:pre)
        {
            cout<<it<<" ";
        }
        cout<<"\n";
        vector<int> post(n+2,1);
        for(int i = n;i>=1;i--)
        {
            post[i]=post[i+1]*nums[i-1];
        }
        post[0]=post[1];
        for(auto it:post)
        {
            cout<<it<<" ";
        }
        cout<<"\n";
        vector<int> ans(n);
        for(int i = 0;i<n;i++)
        {
            ans[i]= pre[i+1-1]*post[i+1+1];
        }
        return ans;
    }
};