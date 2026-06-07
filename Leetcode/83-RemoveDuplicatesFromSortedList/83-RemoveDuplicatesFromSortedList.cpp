// Last updated: 6/7/2026, 11:27:33 PM
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
    ListNode* deleteDuplicates(ListNode* head) {
        if(head==nullptr)
        {
            return head;
        }
        ListNode* cur = head;
        while(cur!=nullptr)
        {
            while(cur->next!=nullptr&&cur->val==cur->next->val)
            {
                cur->next = cur->next->next;
            }
            cur = cur->next;
        }
        return head;
    }
};