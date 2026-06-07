// Last updated: 6/7/2026, 11:26:54 PM
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
    ListNode *detectCycle(ListNode *head) {
        ListNode* slow = head;
        ListNode* fast = head;
        int ans = -1,cycle=0;
        while(fast!=nullptr)
        {
            fast=fast->next;
            if(fast!=nullptr)
            {
                fast=fast->next;
                slow=slow->next;
            }
            if(slow==fast)
            {
                cycle=1;
                break;
            }
        }
        if(cycle==0)
        {
            return nullptr;
        }
        ListNode* meet = slow;
        ListNode* cur = head;
        while(cur!=meet)
        {
            cur=cur->next;
            meet=meet->next;
        }
        ListNode* intersection = meet;
        intersection=intersection->next;
        int length = 1;
        while(intersection!=meet)
        {
            length++;
            intersection=intersection->next;
        }
        ListNode* start = head;
        ans = 0;
        while(start!=meet)
        {
            ans++;
            start=start->next;
        }
        return meet;
    }
};