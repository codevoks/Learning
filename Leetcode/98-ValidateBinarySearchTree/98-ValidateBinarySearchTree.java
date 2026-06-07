// Last updated: 6/7/2026, 11:27:27 PM
/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode() {}
 *     TreeNode(int val) { this.val = val; }
 *     TreeNode(int val, TreeNode left, TreeNode right) {
 *         this.val = val;
 *         this.left = left;
 *         this.right = right;
 *     }
 * }
 */
class Solution {
    public boolean isValidBST(TreeNode root) 
    {
        if(root==null)
        {
            return true;
        }
        if(root.left==null||root.right==null)
        {
            int minv,maxv;
            if(root.left==null&&root.right==null)
            {
                return true;
            }
            else if(root.left==null)
            {
                minv=min(root.right).val;
                if(root.val<minv&&isValidBST(root.right))
                {
                    return true;
                }
                return false;
            }
            else
            {
                maxv=max(root.left).val;
                if(root.val>maxv&&isValidBST(root.left))
                {
                    return true;
                }
                return false;
            }
        }
        if(isValidBST(root.left)&&isValidBST(root.right))
        {
            if(max(root.left).val<root.val&&root.val<min(root.right).val)
            {
                return true;
            }
        }
        return false;
    }
    public TreeNode max(TreeNode rootnode)
    {
        while(rootnode.right!=null)
        {
            rootnode=rootnode.right;
        }
        return rootnode;
    }
    public TreeNode min(TreeNode rootnode)
    {
        while(rootnode.left!=null)
        {
            rootnode=rootnode.left;
        }
        return rootnode;
    }
}