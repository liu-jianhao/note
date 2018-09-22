# 155. 最小栈

## 问题描述
设计一个支持 push，pop，top 操作，并能在常数时间内检索到最小元素的栈。

+ push(x) -- 将元素 x 推入栈中。
+ pop() -- 删除栈顶的元素。
+ top() -- 获取栈顶元素。
+ getMin() -- 检索栈中的最小元素。

示例:
MinStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.getMin();   --> 返回 -3.
minStack.pop();
minStack.top();      --> 返回 0.
minStack.getMin();   --> 返回 -2.

## 解题思路
看到题目第一时间想到的是用一个变量保存最小值，但是这有个问题，如果当最小的元素被弹出栈了，怎么得到下一个最小的元素？

我们接着想，是不是可以将各个阶段的最小值都保存起来，这样就能找到下一个最小的元素了，因此我们添加一个辅助栈，这个栈存储的是各个阶段的最小值，只要压入栈的元素小于最小值就压入这个栈，如果弹出的值等于当前的最小值，那么这个栈也要弹出最小值

```cpp
class MinStack {
public:
    /** initialize your data structure here. */
    MinStack() {
    }
    
    void push(int x) {
        if(m_min.empty() || x <= m_min.top())
        {
            m_min.push(x);
        }
        
        m_data.push(x);
    }
    
    void pop() {
        if(m_data.empty())
            return;
        if(m_data.top() == m_min.top())
        {
            m_min.pop();
        }
        m_data.pop();
    }
    
    int top() {
        return m_data.top();
    }
    
    int getMin() {
        return m_min.top();
    }
    
private:
    stack<int> m_data;
    stack<int> m_min;
};
```