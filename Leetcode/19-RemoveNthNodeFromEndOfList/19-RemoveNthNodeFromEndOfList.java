// Last updated: 6/7/2026, 11:28:01 PM
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
    public ListNode removeNthFromEnd(ListNode head, int n) 
    {
        ListNode temp = head;
        int l = 0;
        while(temp!=null)
        {
            l++;
            temp=temp.next;
        }
        System.out.println("l is "+l);
        temp = head;
        int c=0;
        if(n!=0)
        {
            while(c<l-n-1)
            {
                c++;
                temp=temp.next;
            }
        }
        else
        {
            while(c<l-n-1)
            {
                c++;
                temp=temp.next;
            }
        }
        if(l==n)
        {
            return head.next;
        }
        System.out.println("temp val is "+temp.val);
        temp.next=temp.next.next;
        return head;
    }
}