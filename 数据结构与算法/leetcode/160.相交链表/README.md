# 160. 相交链表

## 问题
编写一个程序，找到两个单链表相交的起始节点。
 
```
例如，下面的两个链表：
A:          a1 → a2
                   ↘
                     c1 → c2 → c3
                   ↗            
B:     b1 → b2 → b3
在节点 c1 开始相交。
```
 

注意：
+ 如果两个链表没有交点，返回 null.
+ 在返回结果后，两个链表仍须保持原有的结构。
+ 可假定整个链表结构中没有循环。
+ 程序尽量满足 O(n) 时间复杂度，且仅用 O(1) 内存。


## 解题思路
只要一个一个节点地比较两条链表，但是要先解决两条链表的长度不等的问题

先得到两条链表的长度，较长的链表的指针先移动长度差个节点，然后它们就在同一起跑线了

```cpp
ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
    if(headA == NULL || headB == NULL)
        return NULL;
    
    int lenA = 0;
    int lenB = 0;
    ListNode *pA = headA;
    ListNode *pB = headB;
    while(pA != NULL)
    {
        lenA++;
        pA = pA->next;
    }
    while(pB != NULL)
    {
        lenB++;
        pB = pB->next;
    }
    
    pA = headA;
    pB = headB;
    if(lenA > lenB)
    {
        for(int i = 0; i < lenA-lenB; ++i)
            pA = pA->next;
    }
    else if(lenA < lenB)
    {
        for(int i = 0; i < lenB-lenA; ++i)
            pB = pB->next;
    }
    
    while(pA != NULL)
    {
        if(pA == pB)
        {
            return pA;
        }
        pA = pA->next;
        pB = pB->next;
    }
    return NULL;
}
```