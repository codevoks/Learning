// Last updated: 6/7/2026, 11:26:51 PM
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
    void f(TreeNode* root,vector<int> &ans)
    {
        if(root==NULL)
        {
            return;
        }
        stack<TreeNode*> s;
        s.push(root);
        while(!s.empty())
        {
            TreeNode* t = s.top();
            ans.push_back(t->val);
            s.pop();
            if(t->right)
            {
                s.push(t->right);
            }
            if(t->left)
            {
                s.push(t->left);
            }
        }
    }
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> ans;
        f(root,ans);
        return ans;
    }
};