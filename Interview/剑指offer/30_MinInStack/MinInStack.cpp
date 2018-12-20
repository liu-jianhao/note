// 面试题30：包含min函数的栈
// 题目：定义栈的数据结构，请在该类型中实现一个能够得到栈的最小元素的min
// 函数。在该栈中，调用min、push及pop的时间复杂度都是O(1)。


class Solution {
public:
    void push(int value) {
        data.push(value);
        if(m.empty() || value < m.top())
        {
            m.push(value);
        }
    }
    void pop() {
        if(!m.empty() && m.top() == data.top())
        {
            m.pop();
        }
        data.pop();
    }
    int top() {
        return data.top();
    }
    int min() {
        return m.top();
    }
    
private:
    stack<int> data;
    stack<int> m;
};