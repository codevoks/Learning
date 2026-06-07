// Last updated: 6/7/2026, 11:26:50 PM
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
    void f(TreeNode* node,vector<int> &ans)
    {
        if(node==NULL)
        {
            return;
        }
        stack<TreeNode*> s1,s2;
        s1.push(node);
        while(!s1.empty())
        {
            TreeNode* t = s1.top();
            s2.push(t);
            s1.pop();
                if(t->left!=NULL)
                {
                    s1.push(t->left);
                }
                if(t->right!=NULL)
                {
                    s1.push(t->right);
                }
            
        }
        while(!s2.empty())
        {
            TreeNode* t = s2.top();
            ans.push_back(t->val);
            s2.pop();
        }
    }
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> ans;
        f(root,ans);
        return ans;
    }
};