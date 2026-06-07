// Last updated: 6/7/2026, 11:25:16 PM
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
    TreeNode* f(int &i,int bound,vector<int> &preorder)
    {
        if(i==preorder.size()||preorder[i]>bound)
        {
            return NULL;
        }
        TreeNode *root = new TreeNode(preorder[i]);
        i++;
        root->left=f(i,root->val,preorder);
        root->right=f(i,bound,preorder);
        return root;
    }
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        //TreeNode* root=new TreeNode(preorder[0]);
        int i=0;
        return f(i,INT_MAX,preorder);
    }
};