// Last updated: 6/7/2026, 11:27:15 PM
/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode() {}
 *     ListNode(int val) { this.val = val; }
 *     ListNode(int val, ListNode next) { this.val = val; this.next = next; }
 * }
 */
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
    public TreeNode sortedListToBST(ListNode head) 
    {
        if(head==null)
        {
            return null;
        }
        if(head.next==null)
        {
            TreeNode t = new TreeNode();
            t.val=head.val;
            return t;
        }
        if(head.next.next==null) return new TreeNode(head.val, null, new TreeNode(head.next.val));
        ListNode temp=head;
        int l=0;
        while(temp!=null)
        {
            l++;
            temp=temp.next;
        }
        int mid = (l+1)/2;
        temp=head;
        ListNode p = head;
        for(int i=1;i<mid;i++)
        {
            if(i==mid-1)
            {
                p = temp;
            }
            temp=temp.next;
        }
        p.next=null;
        ListNode n = temp.next;
        TreeNode root = new TreeNode();
        root.val=temp.val;
        //System.out.println(p.val);
        root.left=sortedListToBST(head);
        root.right=sortedListToBST(n);
        return root;
    }
}