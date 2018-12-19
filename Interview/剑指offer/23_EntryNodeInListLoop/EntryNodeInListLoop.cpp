// 面试题23：链表中环的入口结点
// 题目：一个链表中包含环，如何找出环的入口结点？例如，在图3.8的链表中，
// 环的入口结点是结点3。



struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) :
        val(x), next(nullptr) {
    }
};

class Solution {
public:
    ListNode* EntryNodeOfLoop(ListNode* pHead)
    {
        if(pHead == nullptr || pHead->next == nullptr)
        {
            return nullptr;
        }
        
        ListNode* fast = pHead->next->next;
        ListNode* slow = pHead->next;

        int count = 1;
        while(fast != slow && fast != nullptr)
        {
            fast = fast->next->next;
            slow = slow->next;
            ++count;
        }
        
        fast = pHead;
        while(fast != slow)
        {
            fast = fast->next;
            slow = slow->next;
        }
        
        return fast;
    }
};