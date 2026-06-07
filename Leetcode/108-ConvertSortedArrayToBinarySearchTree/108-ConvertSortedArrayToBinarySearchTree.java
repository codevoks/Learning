// Last updated: 6/7/2026, 11:27:16 PM
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
    public TreeNode sortedArrayToBST(int[] nums) 
    {
        TreeNode root = new TreeNode();
        if(nums.length==0)
        {
            return null;
        }
        int n = nums.length;
        root.val=nums[n/2];
        int []a = new int[n/2];
        int []b = new int [n-n/2 -1];
        for(int i =0;i<n/2;i++)
        {
            a[i]=nums[i];
        }
        for(int i=0;i<n-n/2-1;i++)
        {
            b[i]=nums[i+n/2+1];
        }
        root.left = sortedArrayToBST(a);
        root.right = sortedArrayToBST(b);
        return root;
    }
}