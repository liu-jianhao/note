# 59. 螺旋矩阵 II

## 问题
给定一个正整数 n，生成一个包含 1 到 n2 所有元素，且元素按顺时针顺序螺旋排列的正方形矩阵。


示例:
```
输入: 3
输出:
[
 [ 1, 2, 3 ],
 [ 8, 9, 4 ],
 [ 7, 6, 5 ]
]
```

## 解题思路
与之前的螺旋矩阵I类似，不过这次已经没有特殊情况了，应为这是一个正方形矩阵，因此肯定每次都能扫描一圈(最后一个也算)


```cpp
vector<vector<int>> generateMatrix(int n) {
    if(n <= 0)
        return vector<vector<int>>{};
    
    int num = 1;
    int total = n * n;
    int rowB = 0, rowE = n-1;
    int colB = 0, colE = n-1;
    vector<vector<int>> res(n, vector<int>(n));
    
    while(num <= total)
    {
        for(int i = colB; i <= colE; ++i)
        {
            res[rowB][i] = num++;
        }
        rowB++;
        
        for(int i = rowB; i <= rowE; ++i)
        {
            res[i][colE] = num++;
        }
        colE--;
        
        for(int i = colE; i >= colB; --i)
        {
            res[rowE][i] = num++;
        }
        rowE--;
        
        for(int i = rowE; i >= rowB; --i)
        {
            res[i][colB] = num++;
        }
        colB++;
    }
    
    return res;
}
```