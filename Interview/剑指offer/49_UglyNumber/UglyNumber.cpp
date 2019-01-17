// 面试题49：丑数
// 题目：我们把只包含因子2、3和5的数称作丑数（Ugly Number）。求按从小到
// 大的顺序的第1500个丑数。例如6、8都是丑数，但14不是，因为它包含因子7。
// 习惯上我们把1当做第一个丑数。

class Solution {
public:
    int GetUglyNumber_Solution(int index) {
        if(index < 7)
        {
            return index;
        }
        
        vector<int> ugly(index);
        ugly[0] = 1;
        
        int mul2Index = 0;
        int mul3Index = 0;
        int mul5Index = 0;
        
        for(int i = 1; i < index; ++i)
        {
            ugly[i] = std::min(std::min(ugly[mul2Index] * 2, ugly[mul3Index] * 3), ugly[mul5Index] * 5);
            
            if(ugly[mul2Index] * 2 == ugly[i])
            {
                ++mul2Index;
            }
            if(ugly[mul3Index] * 3 == ugly[i])
            {
                ++mul3Index;
            }
            if(ugly[mul5Index] * 5 == ugly[i])
            {
                ++mul5Index;
            }
        }
        
        return ugly[index-1];
    }
};