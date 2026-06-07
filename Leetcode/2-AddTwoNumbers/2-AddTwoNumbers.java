// Last updated: 6/7/2026, 11:28:08 PM
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
class Solution {
    public ListNode addTwoNumbers(ListNode l1, ListNode l2) 
    {
        ListNode ans = new ListNode();
        int carry = 0;
        int add =0;
        int put = 0;
        ListNode nav = ans;
        while(l1!=null||l2!=null)
        {
            while(l1!=null&&l2!=null)
            {
                ListNode n = new ListNode();
                add=l1.val+l2.val+carry;
                put=add%10;
                carry=add/10;
                n.val=put;
                l1=l1.next;
                l2=l2.next;
                nav.next=n;;
                nav=nav.next;
            }
            while(l1!=null)
            {
                ListNode n = new ListNode();
                add=l1.val+carry;
                put=add%10;
                carry=add/10;
                n.val=put;
                l1=l1.next;
                nav.next=n;
                nav=nav.next;
            }
            while(l2!=null)
            {
                ListNode n = new ListNode();
                add=l2.val+carry;
                put=add%10;
                carry=add/10;
                n.val=put;
                l2=l2.next;
                nav.next=n;
                nav=nav.next;
            }
            if(carry==1)
            {
                ListNode n = new ListNode();
                n.val=carry;
                nav.next=n;
                nav=nav.next;
            }
        }
        ans=ans.next;
        return ans;
    }
}