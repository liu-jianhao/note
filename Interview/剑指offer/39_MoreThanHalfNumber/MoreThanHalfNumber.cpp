// 面试题39：数组中出现次数超过一半的数字
// 题目：数组中有一个数字出现的次数超过数组长度的一半，请找出这个数字。例
// 如输入一个长度为9的数组{1, 2, 3, 2, 2, 2, 5, 4, 2}。由于数字2在数组中
// 出现了5次，超过数组长度的一半，因此输出2。


class Solution {
public:
    int MoreThanHalfNum_Solution2(vector<int> numbers) {
        if(numbers.empty())
        {
            return 0;
        }
        
        int start = 0;
        int end = numbers.size() - 1;
        int middle = numbers.size() / 2;
        
        int index = Partition(numbers, start, end);
        while(index != middle)
        {
            if(index > middle)
            {
                end = index - 1;
                index = Partition(numbers, start, end);
            }
            else
            {
                start = index + 1;
                index = Partition(numbers, start, end);
            }
        }
        
        if(!check(numbers, numbers[index]))
        {
            return 0;
        }
        return numbers[index];
    }
    
    int Partition(vector<int>& numbers, int start, int end)
    {
        int key = numbers[start];
        while(start != end)
        {
            while(numbers[end] > key && start < end)
            {
                --end;
            }
            if(start < end)
            {
                numbers[start] = numbers[end];
                ++start;
            }
            
            while(numbers[start] < key && start < end)
            {
                ++start;
            }
            if(start < end)
            {
                numbers[end] = numbers[start];
                --end;
            }
        }
        numbers[start] = key;
        return start;
    }
    
    bool check(vector<int> numbers, int num)
    {
        int count = 0;
        for(int i = 0; i < numbers.size(); ++i)
        {
            if(num == numbers[i])
            {
                ++count;
            }
        }
        
        if(count > numbers.size()/2)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    
    int MoreThanHalfNum_Solution(vector<int> numbers) {
        if(numbers.empty())
        {
            return 0;
        }
        
        int num = numbers[0];
        int count = 1;
        for(int i = 1; i < numbers.size(); ++i)
        {
            if(num == numbers[i])
            {
                ++count;
            }
            else
            {
                --count;
                if(count == 0)
                {
                    num = numbers[i];
                    count = 1;
                }
            }
        }
        
        if(!check(numbers, num))
        {
            return 0;
        }
        return num;
    }
};