# 组合搜索与启发式方法
穷举效率太差，所以使用回溯算法，它可以为组合搜索算法问题列出所以可能的解。

## 回溯
回溯是一种在搜索空间中对所有可能排布进行迭代遍历的系统性方案。

回溯算法的每一步中，都会扩展某个已经给出的部分解。

回溯构建了一棵存储部分的树，其中每个顶点代表一个部分解。

回溯的构建过程与深度优先遍历是一致的。(深度优先搜索比广度优先搜索占用的空间少)

实现：
```c
#include "backtrack.h"
#include "bool.h"

bool finished = FALSE;       /* found all solutions yet? */

backtrack(int a[], int k, data input)
{
    int c[MAXCANDIDATES];           /* candidates for next position */
    int ncandidates;                /* next position candidate count */
    int i;                          /* counter */

    if (is_a_solution(a,k,input))
            process_solution(a,k,input);
    else {
            k = k+1;
            construct_candidates(a,k,input,c,&ncandidates);
            for (i=0; i<ncandidates; i++) {
                    a[k] = c[i];
        make_move(a,k,input);

                    backtrack(a,k,input);
        if (finished) return;	/* terminate early */

        unmake_move(a,k,input);
            }
    }
}
```

+ `is_a_solution(a, k, input)`——检测测试向量a的前k个元素是否形成完成解，最后一个参数input是传递的信息。
+ `construct_candidates(a, k, input, c, &ncandidates)`——给定数组a中前k-1个位置的内容，
这个函数用a中第k个位置所有可能的候选者去填满数组c(可视为返回的数据)
+ `process_solution(a, k, input)`——一旦某个解构造完毕，这个函数会做你想做的处理
+ `make_move(a, k, input) & make_unmove(a, k, input)`——这两个函数可以我门基于最近一次走子情况来改变数据结构，
也可以在我们决定撤回走子时清理这个数据结构

### 构建全部子集

```c
#include "bool.h"
#include "backtrack.h"

process_solution(int a[], int k)
{
	int i;				/* counter */
	
	printf("{");
	for (i=1; i<=k; i++)
		if (a[i] == TRUE) printf(" %d",i);

	printf(" }\n");
}

is_a_solution(int a[], int k, int n)
{
	return (k == n);
}

make_move(int a[], int k, int n)
{
}

unmake_move(int a[], int k, int n)
{
}

/*	What are possible elements of the next slot in the permutation?  */

construct_candidates(int a[], int k, int n, int c[], int *ncandidates)
{
	c[0] = TRUE;
	c[1] = FALSE;
	*ncandidates = 2;
}
main()
{
	int a[NMAX];			/* solution vector */

	backtrack(a,0,3);
}
```

可能`construct_candidates`这个函数比较难理解一点，`c`这个数组就是用来循环赋值给`a`这个数组，
用来判断第i个数是否在子集中。

输出
```
{ 1 2 3 }
{ 1 2 }
{ 1 3 }
{ 1 }
{ 2 3 }
{ 2 }
{ 3 }
{ }
```

### 构建全部置换(全排列)
```c
#include "bool.h"
#include "backtrack.h"


process_solution(int a[], int k)
{
    int i;				/* counter */

    for (i=1; i<=k; i++) printf(" %d",a[i]);

    printf("\n");
}

bool is_a_solution(int a[], int k, int n)
{
    return (k == n);
}

void make_move(int a[], int k, int n)
{
}

void unmake_move(int a[], int k, int n)
{
}


/*	What are possible elements of the next slot in the permutation?  */

void construct_candidates(int a[], int k, int n, int c[], int *ncandidates)
{
    int i;				/* counter */
    bool in_perm[NMAX];		/* what is now in the permutation? */

    for (i=1; i<NMAX; i++)
        in_perm[i] = FALSE;
    for (i=1; i<k; i++)
        in_perm[ a[i] ] = TRUE;

    *ncandidates = 0;
    for (i=1; i<=n; i++)
        if (in_perm[i] == FALSE) {
            c[ *ncandidates] = i;
            *ncandidates = *ncandidates + 1;
        }
}



int main()
{
    int a[NMAX];			/* solution vector */

    backtrack(a,0,0);
    backtrack(a,0,1);
    backtrack(a,0,2);
    backtrack(a,0,3);

    return 0;
}
```

