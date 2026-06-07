// Last updated: 6/7/2026, 11:26:03 PM
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
    public TreeNode ip(TreeNode n)
    {
        n=n.left;
        while(n.right!=null)
        {
            n=n.right;
        }
        return n;
    }
    
    public TreeNode deleteNode(TreeNode root, int key) {
        if(root==null)
        {
            return null;
        }
        else if(key<root.val)
        {
            root.left=deleteNode(root.left,key);
        }
        else if(key>root.val)
        {
            root.right=deleteNode(root.right,key);
        }
        else
        {
            if(root.left==null&&root.right==null)
            {
                return null;
            }
            if(root.left==null)
            {
                return root.right;
            }
            if(root.right==null)
            {
                return root.left;
            }
            TreeNode x=ip(root);
            root.left=deleteNode(root.left, x.val);
            root.val=x.val;
            return root;
        }
        return root;
        
    }
}