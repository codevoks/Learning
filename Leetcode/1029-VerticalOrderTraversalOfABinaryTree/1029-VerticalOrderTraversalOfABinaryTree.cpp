// Last updated: 6/7/2026, 11:25:22 PM
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<vector<int>> verticalTraversal(TreeNode* root) {
        map<int,map<int,multiset<int>>> mp;
    vector<vector<int>> ans;
    queue<pair<TreeNode*,pair<int,int>>> q;
    q.push({root,{0,0}});
    while(!q.empty())
    {
        //cout<<"bachao"<<endl;
        int s = q.size();
        for(int i = 0;i<s;i++)
        {
            pair<TreeNode*,pair<int,int>> f=q.front();
            q.pop();
            int hd = f.second.first;
            int l = f.second.second;
            TreeNode* n=f.first;
            int value = f.first->val;
            mp[hd][l].insert(value);
            if(n->left)
            {
                q.push({n->left,{hd-1,l+1}});
            }
            if(n->right)
            {
                q.push({n->right,{hd+1,l+1}});
            }
        }
    }
    for(auto &i:mp)
    {
        //cout<<" horizontal is "<<i.first;
        vector<int> a;
        for(auto &j:i.second)
        {
            //cout<<" vertical is "<<j.first;
            for(auto &k:j.second )
            {
              //  cout<<" element is "<<k;
                a.push_back(k);
            }
            //cout<<" vector after innermost loop "<<endl;
            //for(int t = 0;t<a.size();t++)
           // {
            //    cout<<a[t]<<" ";
            //}
        }
        //cout<<endl;
        ans.push_back(a);
    }
    return ans;
    }
};