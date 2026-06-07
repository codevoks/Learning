// Last updated: 6/7/2026, 11:27:22 PM
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
    bool f(TreeNode *node,long mini,long maxi)
    {
        if(node==NULL)
        {
            return true;
        }
        if(node->val<=mini||node->val>=maxi)
        {
            return false;
        }
        return f(node->left,mini,node->val)&&f(node->right,node->val,maxi);
    }
    bool isValidBST(TreeNode* root) {
        return f(root,LONG_MIN,LONG_MAX);      
    }
};