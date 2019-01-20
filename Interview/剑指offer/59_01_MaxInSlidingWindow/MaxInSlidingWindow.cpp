// 面试题59（一）：滑动窗口的最大值
// 题目：给定一个数组和滑动窗口的大小，请找出所有滑动窗口里的最大值。例如，
// 如果输入数组{2, 3, 4, 2, 6, 2, 5, 1}及滑动窗口的大小3，那么一共存在6个
// 滑动窗口，它们的最大值分别为{4, 4, 6, 6, 6, 5}，

class Solution {
public:
    vector<int> maxInWindows(const vector<int>& num, unsigned int size)
    {
        vector<int> res;
        deque<int> s;
        for(unsigned int i = 0; i < num.size(); ++i){
            // 从后面依次弹出队列中比当前num值小的元素，同时也能保证队列首元素为当前窗口最大值下标
            while(s.size() && num[s.back()] <= num[i])
            {
                s.pop_back();
            }

            // 队首元素坐标对应的num不在窗口中，需要弹出
            if(s.size() && i-s.front() + 1 > size)
            {
                s.pop_front();
            }

            // 把每次滑动的num下标加入队列
            s.push_back(i);
            // 当滑动窗口首地址i大于等于size时才开始写入窗口最大值
            if(size && i + 1 >= size)
            {
                res.push_back(num[s.front()]);
            }
        }
        return res;
    }
};