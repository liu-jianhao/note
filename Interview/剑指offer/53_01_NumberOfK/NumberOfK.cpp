// 面试题53（一）：数字在排序数组中出现的次数
// 题目：统计一个数字在排序数组中出现的次数。例如输入排序数组{1, 2, 3, 3,
// 3, 3, 4, 5}和数字3，由于3在这个数组中出现了4次，因此输出4。

class Solution {
public:
    int GetNumberOfK(vector<int> data ,int k) {
        if(data.empty())
        {
            return 0;
        }
        
        int start = GetFirstK(data, k);
        if(start == -1)
        {
            return 0;
        }
        int end = GetLastK(data, k);
        
        return end - start + 1;
    }
    
    int GetFirstK(vector<int> data, int k)
    {
        int start = 0;
        int end = data.size() - 1;
        int mid;
        
        while(start <= end)
        {
            mid = (start + end) / 2;
            
            if(data[mid] > k)
            {
                end = mid - 1;
            }
            else if (data[mid] < k)
            {
                start = mid + 1;
            }
            else
            {
                if(mid == 0 || data[mid-1] != k)
                {
                    break;
                }
                else
                {
                    end = mid - 1;
                }
            }
        }
        if(start > end)
        {
            return -1;
        }
        return mid;
    }
    
    int GetLastK(vector<int> data, int k)
    {
        int start = 0;
        int end = data.size() - 1;
        int mid;
        
        while(start <= end)
        {
            mid = (start + end) / 2;
            
            if(data[mid] > k)
            {
                end = mid - 1;
            }
            else if (data[mid] < k)
            {
                start = mid + 1;
            }
            else
            {
                if(mid == data.size()-1 || data[mid+1] != k)
                {
                    break;
                }
                else
                {
                    start = mid + 1;
                }
            }
        }
        return mid;
    }
};