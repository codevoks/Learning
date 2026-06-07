// Last updated: 6/7/2026, 11:27:54 PM
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
    ListNode* reverseKGroup(ListNode* head, int k) {
        if(head==nullptr)
        {
            return head;
        }
        ListNode* d = head;
        for(int i =1;i<=k;i++)
        {
            if(d==nullptr)
            {
                return head;
            }
            d=d->next;
        }
        ListNode* copy = head;
        ListNode* cur = head;
        ListNode* prev = nullptr;
        for(int i =1;i<=k;i++)
        {
            ListNode* n = cur->next;
            cur->next = prev;
            prev = cur;
            cur = n;
        }
        //check if we have more k sized chunks
        copy->next = reverseKGroup(cur,k);
        return prev;
    }
};