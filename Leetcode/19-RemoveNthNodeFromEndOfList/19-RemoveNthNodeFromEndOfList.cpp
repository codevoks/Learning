// Last updated: 6/7/2026, 11:27:56 PM
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
    ListNode* removeNthFromEnd(ListNode* head, int N) {
        if(head==nullptr)
    {
        return head;
    }
    int n = 0;
    ListNode* cur = head;
    while(cur!=nullptr)
    {
        n++;
        cur = cur->next;
    }
    int k = n-N;
    if(k==0)
    {
        return head->next;
    }
    else
    {
        cout<<" k is "<<k<<"\n";
    cur = head;
    for(int i = 1;i<=k-1;i++)
    {
        cur = cur->next;
    }
    cout<<cur->val<<"\n";
    cur->next=cur->next->next;
    return head;
    }
    }
};