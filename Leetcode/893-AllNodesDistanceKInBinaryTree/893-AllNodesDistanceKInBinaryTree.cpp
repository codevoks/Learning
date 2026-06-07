// Last updated: 6/7/2026, 11:25:31 PM
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    void f(unordered_map<TreeNode*,TreeNode*> &parentof,TreeNode* root)
    {
        if(root==NULL)
        {
             return;
        }
        if(root->left)
        {
             parentof.insert({root->left,root});
        }
        if(root->right)
        {
            parentof.insert({root->right,root});
        }
                     f(parentof,root->left);
                     f(parentof,root->right);


        return;
    }
    vector<int> distanceK(TreeNode* root, TreeNode* target, int k) 
    {
        unordered_map<TreeNode*,TreeNode*> parentof;
        unordered_map<TreeNode*,bool> vis;
        f(parentof,root);
        queue<TreeNode*> q;
        vector<int> ans;
        if(root==NULL)
        {
            return ans;
        }
        TreeNode* node=target;
        q.push(node);
        vis[node]=true;
        //int p=0;
        while(k)
        {
            //cout<<1+p<<" size of q is "<<q.size()<< endl;
            //p++;
            int s = q.size();
            for(int i =0;i<s;i++)
            {
                TreeNode* f = q.front();
                q.pop();
                vis[f]=true;
                if(!vis[parentof[f]]&&parentof[f]!=NULL)
                {
                    q.push(parentof[f]);
                }
                if(f->left!=NULL&&vis.find(f->left)==vis.end())
                {
                    q.push(f->left);
                }
            
                if(f->right!=NULL&&vis.find(f->right)==vis.end())
                {
                    q.push(f->right);
                }
            }
            k--;
        }
        while(!q.empty())
        {
            ans.push_back(q.front()->val);
            q.pop();
        }
        return ans;
        }
    };