// Last updated: 6/7/2026, 11:26:56 PM
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    bool hasCycle(ListNode *head) {
        if(head==NULL)
        {
            return 0;
        }
        ListNode* slow = head;
        ListNode* fast = head;
        while(fast!=NULL)
        {
            fast = fast->next;
            if(fast!=NULL)
            {
                fast=fast->next;
                slow=slow->next;
            }
            if(slow==fast)
            {
                break;
            }
        }
        return fast==slow;
    }
};