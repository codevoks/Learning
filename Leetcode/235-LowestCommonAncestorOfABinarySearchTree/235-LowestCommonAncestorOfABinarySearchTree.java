// Last updated: 6/7/2026, 11:26:29 PM
/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode(int x) { val = x; }
 * }
 */

class Solution {
    public TreeNode lowestCommonAncestor(TreeNode root, TreeNode p, TreeNode q) {
        List<TreeNode> a = helper(root,p);
        List<TreeNode> b = helper(root,q);
        for(int i=0;i<a.size();i++)
        {
            TreeNode c = a.get(i);
            for(int j=0;j<b.size();j++)
            {
                if(b.contains(c))
                {
                    return c;
                }
            }
        }
        return null;
    }
    public List<TreeNode> helper(TreeNode rootnode,TreeNode t)
    {
        List<TreeNode> ans = new ArrayList<>();
        while(rootnode!=null)
        {
            ans.add(0,rootnode);
            if(t.val==rootnode.val)
            {
                break;
            }
            else if(t.val<rootnode.val)
            {
                rootnode = rootnode.left;
            }
            else
            {   
                rootnode = rootnode.right;
            }
        }
        return ans;
    }
}