// Last updated: 6/7/2026, 11:24:52 PM
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

    ListNode* pre(ListNode* head)
    {
        ListNode* prev = nullptr;
        ListNode* slow = head; 
        ListNode* fast = head;
        while(fast!=nullptr)
        {
            fast = fast->next;
            if(fast!=nullptr)
            {
                slow = slow->next;
                fast = fast->next;
                if(prev==nullptr)
                {
                    prev = head;
                }
                else
                {
                    prev = prev->next;
                }
            }
        }
        return prev;
    }

    ListNode* deleteMiddle(ListNode* head) {
        if(head==nullptr)
        {
            return head;
        }
        ListNode* prev = pre(head);
        if(prev!=nullptr)
        {
            cout<<" prev's val is "<<prev->val<<"\n";
            prev->next = prev->next->next;
        }
        else
        {
            head = nullptr;
        }
        return head;
    }
};