// Last updated: 6/7/2026, 11:27:13 PM
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
int isleaf(TreeNode* node)
{
    return node->left==NULL&&node->right==NULL;
}
    bool hasPathSum(TreeNode* root, int targetSum) {
        if(root==NULL)
        {
            return 0;
        }
        if(targetSum==root->val&&isleaf(root))
        {
            return 1;
        }
        int l = hasPathSum(root->left,targetSum-root->val);
        int r = hasPathSum(root->right,targetSum-root->val);
        return l||r;
    }
};