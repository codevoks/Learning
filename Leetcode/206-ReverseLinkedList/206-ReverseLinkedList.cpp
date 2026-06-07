// Last updated: 6/7/2026, 11:26:31 PM
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* reverseList(ListNode* head) 
    {
        if(head==nullptr)
        {
            return head;
        }
        ListNode* copy = head;
        ListNode* prev = nullptr;
        ListNode* cur = head;
        while(cur!=nullptr)
        {
            ListNode* n = cur->next;
            cur->next = prev;
            prev=cur;
            cur = n;
        }
        return prev;
    }
};