// Last updated: 6/7/2026, 11:25:39 PM
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
    public TreeNode insertIntoBST(TreeNode root, int val) 
    {
        TreeNode r = new TreeNode();
        if(root==null)
        {
            r.val = val;
            r.left = null;
            r.right = null;
            root=r;
            return root;
        }
        if(root.right==null||root.left==null)
        {
            if(root.left==null&&root.right==null)
            {
                if(val<=root.val)
                {
                    r.val=val;
                    r.left=null;
                    r.right=null;
                    root.left=r;
                    return root;
                }
                else
                {
                    r.val=val;
                    r.left=null;
                    r.right=null;
                    root.right=r;
                    return root;
                }
            }
            else if(root.left==null)
            {
                r.val=val;
                r.left=null;
                r.right=null;
                //root.right=r;
                if(val<=root.val)
                root.left= insertIntoBST(root.left,val);
                else
                root.right = insertIntoBST(root.right,val);
                return root;
            }
            else
            {
                r.val=val;
                r.left=null;
                r.right=null;
                //root.left=r;
                if(val>root.val)
                root.right=insertIntoBST(root.right,val);
                else
                    root.left=insertIntoBST(root.left,val);
                return root;
            }
        }
        if(val<=root.val)
        {
            root.left=insertIntoBST(root.left,val);
            return root;
        }
        else
        {
            root.right=insertIntoBST(root.right,val);
            return root;
        }
        
    }
}