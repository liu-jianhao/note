// 面试题18（二）：删除链表中重复的结点
// 题目：在一个排序的链表中，如何删除重复的结点？例如，在图3.4（a）中重复
// 结点被删除之后，链表如图3.4（b）所示。



struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) :
        val(x), next(nullptr) {
    }
};

class Solution {
public:
    ListNode* deleteDuplication(ListNode* pHead)
    {
        if(pHead == nullptr || pHead->next == nullptr)
        {
            return pHead;
        }
        
        ListNode* pPre = nullptr;
        ListNode* p = pHead;
        while(p)
        {
            ListNode* pNext = p->next;
            // 有重复的节点
            if(pNext != nullptr && pNext->val == p->val)
            {
                // 找到连续重复节点的最后一个节点
                while(pNext->next && pNext->next->val == pNext->val)
                {
                    pNext = pNext->next;
                }
                
                // p是头结点
                if(pPre == nullptr)
                {
                    pHead = pNext->next;
                }
                else
                {
                    pPre->next = pNext->next;
                }
                p = pNext->next;
            }
            else
            {
                pPre = p;
                p = p->next;
            }
        }
        
        return pHead;
    }
};