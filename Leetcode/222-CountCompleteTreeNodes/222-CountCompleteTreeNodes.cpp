// Last updated: 6/7/2026, 11:26:25 PM
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
    int f(TreeNode* root)
    {
        if(root==NULL)
        {
            return 0;
        }
        int l = lh(root);
        int r = rh(root);
        if(l==r)
        {
            return (1<<l)-1;
        }
        else
        {
            return 1 + f(root->left) + f(root->right);
        }
    }
    int lh(TreeNode* node)
    {
        int c=0;
        while(node)
        {
            c++;
            node=node->left;
        }
        return c;
    }
    int rh(TreeNode* node)
    {
        int c=0;
        while(node)
        {
            c++;
            node=node->right;
        }
        return c;
    }
    int countNodes(TreeNode* root) {
        
        return f(root);
    }
};