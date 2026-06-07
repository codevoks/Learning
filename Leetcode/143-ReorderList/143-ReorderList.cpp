// Last updated: 6/7/2026, 11:26:53 PM
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

    // ListNode* middle(ListNode* &head)
    // {
    //     ListNode* slow = head;
    //     ListNode* fast = head;
    //     while(fast!=nullptr)
    //     {
    //         fast = fast->next;
    //         if(fast!=nullptr)
    //         {
    //             fast=fast->next;
    //             slow=slow->next;
    //         }
    //     }
    //     return slow;
    // }

    // ListNode* reverse(ListNode* &head)
    // {
    //     if(head==nullptr)
    //     {
    //         return head;
    //     }
    //     ListNode* n = head->next;
    //     ListNode* new_head = head;
    //     if(head->next!=nullptr)
    //     {
    //         new_head = reverse(head->next);
    //         n->next = head;
    //     }
    //     head->next = nullptr;
    //     return new_head;
    // }

    // ListNode* merge(ListNode* &h1,ListNode* &h2)
    // {
    //     ListNode* head = h1;
    //     ListNode* cur1 = h1;
    //     ListNode* cur2 = h2;
    //     while(cur1!=nullptr&&cur2!=nullptr)
    //     {
    //         ListNode* n1 = cur1->next;
    //         ListNode* n2 = cur2->next;
    //         cur1->next = cur2;
    //         cur2->next = n1;
    //         cur1 = n1;
    //         cur2 = n2;
    //     }
    //     return h1;
    // }

    ListNode* middle(ListNode* &head)
{
    ListNode* slow = head;
    ListNode* fast = head;
    while(fast!=nullptr)
    {
        fast = fast->next;
        if(fast!=nullptr)
        {
            fast=fast->next;
            slow=slow->next;
        }
    }
    return slow;
}

ListNode* reverse(ListNode* &head)
{
    if(head==nullptr)
    {
        return head;
    }
    ListNode* copy = head;
    ListNode* d = head->next;
    ListNode* ans = head;
    if(head->next!=nullptr)
    {
		ans= reverse(head->next);
        d->next=copy;
    }
    copy->next=nullptr;
    return ans;
}

ListNode* merge(ListNode* &h1,ListNode* &h2)
{
    ListNode* head = h1;
    ListNode* cur1 = h1;
    ListNode* cur2 = h2;
    while(cur1!=nullptr&&cur2!=nullptr)
    {
        ListNode* n1 = cur1->next;
        ListNode* n2 = cur2->next;
        cur1->next = cur2;
        cur2->next = n1;
        cur1 = n1;
        cur2 = n2;
    }
    return head;
}

    void reorderList(ListNode* head) {
        //find the middle
        ListNode* mid = middle(head);
        //split at mid's next and set mid's next to null
        ListNode* head2 = mid;
        head2 = mid->next;
        mid->next = nullptr;
        //reverse second list
        ListNode* head3 = reverse(head2);
        //merge
        merge(head,head3);
    }
};