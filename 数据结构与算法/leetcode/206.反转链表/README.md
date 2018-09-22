# 206. 反转链表

## 问题
反转一个单链表。

```
示例:
输入: 1->2->3->4->5->NULL
输出: 5->4->3->2->1->NULL
```

```
进阶:
你可以迭代或递归地反转链表。你能否用两种方法解决这道题？
```



### 解决思路
要反转一个链表，那就需要有三个指针，否则会断掉，而且最后返回的头结点是原本的最后一个元素

#### C++
```cpp
ListNode* reverseList(ListNode* head) {
    if(head == NULL || head->next == NULL)
        return head;
    
    ListNode* pre = NULL;
    ListNode* next = NULL;
    
    while(head != NULL) {
        next = head->next;
        head->next = pre;
        pre = head;
        head = next;
    }
    
    return pre;
}
```

#### Go
```go
func reverseList(head *ListNode) *ListNode {
    if head == nil || head.Next == nil {
        return head
    }
    
    var pre *ListNode
    var next *ListNode
    
    for head != nil {
        next = head.Next
        head.Next = pre
        pre = head
        head = next
    }
    
    return pre
}
```