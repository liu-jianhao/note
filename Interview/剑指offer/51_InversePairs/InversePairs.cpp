// 面试题51：数组中的逆序对
// 题目：在数组中的两个数字如果前面一个数字大于后面的数字，则这两个数字组
// 成一个逆序对。输入一个数组，求出这个数组中的逆序对的总数。

class Solution {
public:
    int InversePairs(vector<int> data) {
        if(data.empty())
        {
            return 0;
        }
        
        //vector<int> copy = data;
        vector<int> copy(data.size());
        return InversePairs(data, copy, 0, data.size()-1) % 1000000007;
    }
    
    // 返回逆序对的个数
   long long InversePairs(vector<int>& data, vector<int>& copy, int start, int end)
    {
        if(start == end)
        {
            copy[start] = data[start];
            return 0;
        }
        
        int mid = (start + end) / 2;
        long long left = InversePairs(data, copy, start, mid);
        long long right = InversePairs(data, copy, mid+1, end);
        
        
        int i = mid;
        int j = end;
        int copyIndex = end;
        long long count = 0;
        
        while(i >= start && j >= mid+1)
        {
            if(data[i] > data[j])
            {
                copy[copyIndex--] = data[i--];
                count += j - mid; // 加上右边序列的逆序对个数
            }
            else
            {
                copy[copyIndex--] = data[j--];
            }
        }
        
        for(; i >= start; --i)
        {
            copy[copyIndex--] = data[i];
        }
        for(; j >= mid+1; --j)
        {
            copy[copyIndex--] = data[j];
        }
        
        // 注意这里，由于已经进行了一次合并，所以要修改data数组，以免重复计算
        
        for(int s = start; s <= end; ++s)
        {
            data[s] = copy[s];
        }
        
        return left + right + count;
    }
};