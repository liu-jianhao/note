// 面试题33：二叉搜索树的后序遍历序列
// 题目：输入一个整数数组，判断该数组是不是某二叉搜索树的后序遍历的结果。
// 如果是则返回true，否则返回false。假设输入的数组的任意两个数字都互不相同。


class Solution {
public:
    bool VerifySquenceOfBST(vector<int> sequence) {
        return VerifySquenceOfBST(sequence, 0, sequence.size()-1);
    }
    
    bool VerifySquenceOfBST(vector<int> sequence, int start, int end)
    {
        if(sequence.empty() || end < start)
        {
            return false;
        }
        
        int root = sequence[end];
        
        int i = start;
        for(; i < end; ++i)
        {
            if(sequence[i] > root)
            {
                break;
            }
        }
        
        int j = i;
        for(; j < end; ++j)
        {
            if(sequence[j] < root)
            {
                return false;
            }
        }
        
        bool left, right;
        left = right = true;
        if(i > start)
            left = VerifySquenceOfBST(sequence, start, i-1);
        if(i < end-1)
            right = VerifySquenceOfBST(sequence, i, end-1);
        
        return left && right;
    }
};