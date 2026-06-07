// Last updated: 6/7/2026, 11:27:18 PM
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
    TreeNode* tree(vector<int>& inorder,int s1,int e1,vector<int>& postorder,int s2,int e2,unordered_map<int,int> &mp)
    {
        int s = e1-s1+1;
        if(s==0)
        {
            return NULL;
        }
        TreeNode* root = new TreeNode(postorder[e2]);
        int ind = mp[postorder[e2]];
        int sz1 = ind - s1;
        int sz2 = e1-ind;
        root->left = tree(inorder,s1,ind-1,postorder,s2,s2+sz1-1,mp);
        root->right = tree(inorder,ind+1,e1,postorder,s2+sz1,e2-1,mp);
        return root;
    }
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        unordered_map<int,int> mp;
        for(int i = 0;i<inorder.size();i++)
        {
            mp[inorder[i]]=i;
        }
        int s = inorder.size()-1;
        return tree(inorder,0,s,postorder,0,s,mp);
    }
};