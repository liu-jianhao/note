# 141. 环形链表

## 问题
给定一个链表，判断链表中是否有环。

进阶：
你能否不使用额外空间解决此题？

## 解题思路
先假设如果链表有环，那么如果一个指针不停地向前移动那么就会不停地在环中转圈，如果有两个不同速度的指针向前移动，那么它们在环中肯定会相遇

```cpp
bool hasCycle(ListNode *head) {
    if(head == NULL)
        return false;
    ListNode* fast = head;
    ListNode* slow = head;
    while(fast->next != NULL && fast->next->next != NULL){
        fast = fast->next->next;
        slow = slow->next;
        if(fast == slow){
            return true;
        }
    }
    return false;
}
```