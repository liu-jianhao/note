# 54. 螺旋矩阵

## 题目
给定一个包含 m x n 个元素的矩阵（m 行, n 列），请按照顺时针螺旋顺序，返回矩阵中的所有元素。
```
示例 1:
输入:
[
 [ 1, 2, 3 ],
 [ 4, 5, 6 ],
 [ 7, 8, 9 ]
]
输出: [1,2,3,6,9,8,7,4,5]
```
```
示例 2:
输入:
[
  [1, 2, 3, 4],
  [5, 6, 7, 8],
  [9,10,11,12]
]
输出: [1,2,3,4,8,12,11,10,9,5,6,7]
```

## 解题思路
思路也很好想，只要注意打印时的边界问题

要处理两种特殊情况：一种是只有一行，一种是只有一列，其他的情况都是可以完成一圈的扫描


```cpp
vector<int> spiralOrder(vector<vector<int>>& matrix) {
    if(matrix.empty())
        return vector<int>{};
    
    int rowB = 0, rowE = matrix.size()-1;
    int colB = 0, colE = matrix[0].size()-1;
    
    vector<int> res;
    
    while(rowB <= rowE && colB <= colE)
    {
        // 只有一行
        if(rowB == rowE)
        {
            for(int i = colB; i <= colE; ++i)
            {
                res.push_back(matrix[rowB][i]);
            }
            rowB++;
        }
        // 只有一列
        else if(colB == colE)
        {
            for(int i = rowB; i <= rowE; ++i)
            {
                res.push_back(matrix[i][colB]);
            }
            colB++;
        }
        else
        {
            int cur = colB;
            while(cur <= colE)
            {
                res.push_back(matrix[rowB][cur]);
                cur++;
            }
            rowB++;
            
            cur = rowB;
            while(cur <= rowE)
            {
                res.push_back(matrix[cur][colE]);
                cur++;
            }
            colE--;
            
            cur = colE;
            while(cur >= colB)
            {
                res.push_back(matrix[rowE][cur]);
                cur--;
            }
            rowE--;
            
            cur = rowE;
            while(cur >= rowB)
            {
                res.push_back(matrix[cur][colB]);
                cur--;
            }
            colB++;
        }
    }
    
    return res;
}
```