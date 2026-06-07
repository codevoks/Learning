// Last updated: 6/7/2026, 11:27:19 PM
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
    void f(TreeNode* root,vector<vector<int>>& ans)
    {
        if(root==NULL)
        {
            return;
        }
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty())
        {
            vector<int> level;
            int s=q.size();
            for(int i = 1;i<=s;i++)
            {
                TreeNode* f = q.front();
                if(f->left)
                {
                    q.push(f->left);
                }
                if(f->right)
                {
                    q.push(f->right);
                }
                level.push_back(f->val);
                q.pop();
            }
            ans.push_back(level);
        }
    }
    vector<vector<int>> levelOrder(TreeNode* root) 
    {
        vector<vector<int>> ans;
        f(root,ans);
        return ans;
    }
};