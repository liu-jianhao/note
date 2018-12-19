// 面试题22：链表中倒数第k个结点
// 题目：输入一个链表，输出该链表中倒数第k个结点。为了符合大多数人的习惯，
// 本题从1开始计数，即链表的尾结点是倒数第1个结点。例如一个链表有6个结点，
// 从头结点开始它们的值依次是1、2、3、4、5、6。这个链表的倒数第3个结点是
// 值为4的结点。


struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
			val(x), next(nullptr) {
	}
};

class Solution {
public:
    ListNode* FindKthToTail(ListNode* pListHead, unsigned int k) {
        if(pListHead == nullptr || k <= 0)
        {
            return nullptr;
        }
        
        ListNode* pAhead = pListHead;
        for(unsigned int i = 0; i < k-1; ++i)
        {
            if(pAhead->next != nullptr)
            {
                pAhead = pAhead->next;
            }
            else
            {
                return nullptr;
            }
        }
        
        ListNode* pNode = pListHead;
        while(pAhead->next != nullptr)
        {
            pNode = pNode->next;
            pAhead = pAhead->next;
        }
        
        return pNode;
    }
};