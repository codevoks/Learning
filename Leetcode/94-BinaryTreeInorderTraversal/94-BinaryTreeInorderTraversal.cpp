// Last updated: 6/7/2026, 11:27:26 PM
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
        stack<TreeNode*> s;
        //s.push(node);
        while(true)
        {
            if(node!=NULL)
            {
                s.push(node);
                node=node->left;
            }
            else
            {
                if(s.empty())
                {
                    break;
                }
                node = s.top();
                s.pop();
                ans.push_back(node->val);
                node=node->right;
            }
        }
    }
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> ans;
        f(root,ans);
        return ans;
    }
};