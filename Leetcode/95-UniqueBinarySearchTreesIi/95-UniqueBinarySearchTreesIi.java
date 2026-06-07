// Last updated: 6/7/2026, 11:27:24 PM
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
    public List<TreeNode> generateTrees(int n) {
        return helper(1,n);
    }
    public List<TreeNode> helper(int start,int end)
    {
        List<TreeNode> ans = new ArrayList<>();
        if(start==end)
        {
            TreeNode s = new TreeNode(start);
            ans.add(s);
            return ans;
        }
        if(start>end)
        {
            ans.add(null);
            return ans;
        }
        for(int i=start;i<=end;i++)
        {
            List<TreeNode> leftl = helper(start,i-1);
            List<TreeNode> rightl = helper(i+1,end);
            for(int j=0;j<leftl.size();j++)
            {
                //TreeNode l = left.get(j);
                for(int k=0;k<rightl.size();k++)
                {
                    //TreeNode r = right.get(k);
                    TreeNode root = new TreeNode(i);
                    root.left=leftl.get(j);
                    root.right=rightl.get(k);
                    ans.add(root);
                }
            }
        }
        return ans;
    }
}