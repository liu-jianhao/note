# 21. 合并两个有序链表

## 题目
将两个有序链表合并为一个新的有序链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。 

示例：
输入：1->2->4, 1->3->4
输出：1->1->2->3->4->4

## 解题思路
这道题思路很简单，但是写代码时要注意一些细节问题

我将第一个值较小的链表的头结点作为返回结果的头节点，之后保存`pre`为上次已经合并的链表的节点，`cur1`和`cur2`为要比较的两个节点，`else`的操作就是将节点插入结果链表

## C++
```cpp
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    if(l1 == NULL || l2 == NULL) {
        return l1 != NULL ? l1 : l2;
    }
    
    ListNode* head = l1->val < l2->val ? l1 : l2;
    ListNode* cur1 = head == l1 ? l1 : l2;
    ListNode* cur2 = head == l1 ? l2 : l1;
    ListNode* pre = NULL; // 上次比较值较小的节点
    ListNode* next = NULL;
    while(cur1 != NULL && cur2 != NULL) {
        if(cur1->val <= cur2->val) {
            pre = cur1;
            cur1 = cur1->next;
        } else {
            next = cur2->next;
            pre->next = cur2;
            cur2->next = cur1;
            pre = cur2;
            cur2 = next;
        }
    }
    pre->next = cur1 == NULL ? cur2 : cur1;
    return head;
}
```

还有一种代码比较简单的解法，就是采用递归：
```cpp
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2)
    {
        if(l1==NULL)return l2;
        if(l2==NULL)return l1;
        if(l1->val>l2->val){
            l2->next=mergeTwoLists(l1,l2->next);
            return l2;
        }else{
            l1->next=mergeTwoLists(l1->next,l2);
            return l1;
        }
    }
```

## Go
```go
func mergeTwoLists(l1 *ListNode, l2 *ListNode) *ListNode {
    if l1 == nil {
        return l2
    }

    if l2 == nil {
        return l1
    }
    
    var head *ListNode
    var cur1 *ListNode
    var cur2 *ListNode
    var pre *ListNode
    var next * ListNode
    
    if l1.Val < l2.Val {
        head = l1
        cur1 = l1
        cur2 = l2
    } else {
        head = l2
        cur2 = l1
        cur1 = l2
    }
    
    for cur1 != nil && cur2 != nil {
        if cur1.Val <= cur2.Val {
            pre = cur1
            cur1 = cur1.Next
        } else {
            next = cur2.Next
            pre.Next = cur2
            cur2.Next = cur1
            pre = cur2
            cur2 = next
        }
    }
    
    if cur1 != nil {
        pre.Next = cur1
    }
    if cur2 != nil {
        pre.Next = cur2
    }
    
    return head
}
```


```go
func mergeTwoLists(l1 *ListNode, l2 *ListNode) *ListNode {
    if l1 == nil {
        return l2
    }

    if l2 == nil {
        return l1
    }
    
    if l1.Val < l2.Val {
        l1.Next = mergeTwoLists(l1.Next, l2)
        return l1
    } else {
        l2.Next = mergeTwoLists(l1, l2.Next)
        return l2
    }
}
```