// 面试题24：反转链表
// 题目：定义一个函数，输入一个链表的头结点，反转该链表并输出反转后链表的
// 头结点。


struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
			val(x), next(nullptr) {
	}
};
class Solution {
public:
    ListNode* ReverseList(ListNode* pHead) {
        if(pHead == nullptr || pHead->next == nullptr)
        {
            return pHead;
        }
        
        ListNode* pPre = nullptr;
        ListNode* pCur = pHead;
        
        while(pCur != nullptr)
        {
            ListNode* pNext = pCur->next;
            if(pNext == nullptr)
            {
                pHead = pCur;
            }
            
            pCur->next = pPre;
            
            pPre = pCur;
            pCur = pNext;
        }
        
        return pHead;
    }
};