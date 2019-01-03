// 面试题35：复杂链表的复制
// 题目：请实现函数ComplexListNode* Clone(ComplexListNode* pHead)，复
// 制一个复杂链表。在复杂链表中，每个结点除了有一个m_pNext指针指向下一个
// 结点外，还有一个m_pSibling 指向链表中的任意结点或者nullptr。



struct RandomListNode {
    int label;
    struct RandomListNode *next, *random;
    RandomListNode(int x) :
            label(x), next(NULL), random(NULL) {
    }
};

class Solution {
public:
    RandomListNode* Clone(RandomListNode* pHead)
    {
        if(pHead == nullptr)
        {
            return nullptr;
        }
        
        RandomListNode* ret = new RandomListNode(pHead->label);
        
        unordered_map<RandomListNode*, RandomListNode*> map;
        
        RandomListNode* pR = ret;
        RandomListNode* pH = pHead;
        
        map.insert(make_pair(pH, pR));
        while(pH->next)
        {
            pR->next = new RandomListNode(pH->next->label);
            map.insert(make_pair(pH->next, pR->next));
            pH = pH->next;
            pR = pR->next;
        }
        
        pR = ret;
        pH = pHead;

        while(pH)
        {
            if(pH->random != nullptr)
            {
                pR->random = map[pH->random];
            }
            pH = pH->next;
            pR = pR->next;
        }
        
        return ret;
    }
};