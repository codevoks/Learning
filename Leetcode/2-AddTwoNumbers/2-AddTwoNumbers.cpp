// Last updated: 6/7/2026, 11:28:05 PM
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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* cur1 = l1;
        ListNode* cur2 = l2;
        ListNode* head = nullptr;
        ListNode* prev = nullptr;
        int place=0;
        int carry=0;
        while(cur1!=nullptr&&cur2!=nullptr)
        {
            place = cur1->val+cur2->val+carry;
            carry = place/10;
            place = place%10;
            ListNode* cur = new ListNode(place);
            if(prev==nullptr)
            {
                head = cur;
            }
            else
            {
                prev->next=cur;
            }
            prev = cur;
            cur1=cur1->next;
            cur2=cur2->next;
        }
        if(cur2!=nullptr)
        {
            swap(cur1,cur2);
        }
        while(cur1!=nullptr)
        {
            place = cur1->val+carry;
            carry = place/10;
            place=place%10;
            ListNode* cur = new ListNode(place);
            if(prev==nullptr)
            {
                head=cur;
            }
            else
            {
                prev->next=cur;
            }
            prev=cur;
            cur1=cur1->next;
        }
        if(carry)
        {
            ListNode* cur = new ListNode(carry);
            prev->next = cur;
        }
        return head;
    }
};