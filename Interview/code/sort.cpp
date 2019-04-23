#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

const int num = 10000;

template<class T>
void init(T data[])
{
    srand((unsigned)time(NULL));
    for(int i = 0; i < num; i++)
    {
        data[i] = rand()%num;
    }
}

template<class T>
void print(T data)
{
    for(int i = 0; i < num; i++)
    {
        cout << data[i] << endl;
    }
}

template<class T>
void insertionsort(T data[], int n)
{
    for(int i = 1, j; i < n; i++)
    {
        for(j = i; j > 0 && data[j] < data[j-1]; j--)
        {
            int tmp = data[j];
            data[j] = data[j-1];
            data[j-1] = tmp;
            /* swap(data[j-1], data[j]); */
        }
    }
}



template<class T>
void selectsort(T data[], int n)
{
    for(int i = 0, j, least; i < n-1; i++)
    {
        for(j = i+1, least = i; j < n; j++)
        {
            if(data[j] < data[least])
            {
                least = j;
            }
        }
        /* swap(data[least], data[i]); */
        int tmp = data[least];
        data[least] = data[i];
        data[i] = tmp;
    }
}


template<class T>
void bubblesort(T data[], int n)
{
    bool again = true;
    for(int i = 0; i < n-1 && again; i++)
    {
        for(int j = n - 1, again = false; j > i; j--)
        {
            if(data[j] < data[j-1])
            {
                int tmp = data[j];
                data[j] = data[j-1];
                data[j-1] = tmp;
                /* swap(data[j], data[j-1]); */
                again = true;
            }
        }
    }
}


/* 梳排序 */
/* template<class T> */
/* void combsort(T data[], const int n) */
/* { */
/*     int step = n, j, k; */
/*     while((step = int(step/1.3)) > 1) */
/*     { */
/*         for(j = n - 1; j >= step; j--) */
/*         { */
/*             k = j - step; */
/*             if(data[j] < data[k]) */
/*                 swap(data[j], data[k]); */
/*         } */
/*     } */

/*     bool again = true; */
/*     for(int i = 0; i < n-1 && again; i++) */
/*     { */
/*         for(int j = n - 1, again = false; j > i; j--) */
/*         { */
/*             if(data[j] < data[j-1]) */
/*             { */
/*                 swap(data[j], data[j-1]); */
/*                 again = true; */
/*             } */
/*         } */
/*     } */
/* } */


template<class T>
void shellsort(T data[], int arrSize)
{
    int i, j, hCnt, h;
    int increments[20], k;
    /* 先计算出增量值 */
    for(h = 1, i = 0; h < arrSize; i++)
    {
        increments[i] = h;
        h = 3*h + 1;
    }

    for(i--; i >= 0; i--)
    {
        h = increments[i];

        for(hCnt = h; hCnt < 2*h; hCnt++)
        {
            for(j = hCnt; j < arrSize; )
            {
                T tmp = data[j];
                k = j;
                while(k-h > 0 && tmp < data[k-h])
                {
                    data[k] = data[k-h];
                    k -= h;
                }
                data[k] = tmp;
                j += h;
            }
        }
    }
}


/* 将根元素沿树向下移动的算法 */
template<class T>
void moveDown(T data[], int first, int last)
{
    /* first是父节点，last是最后一个元素的下标 */
    int largest = 2 * first + 1; //父节点的左儿子
    while(largest <= last)
    {
        /* 比较左右儿子节点，找到更大的那个 */
        if(largest < last && data[largest] < data[largest+1])
            largest++;

        /* 将小的值moveDown */
        if(data[first] < data[largest])
        {
            swap(data[first], data[largest]);
            first = largest;
            largest = 2 * first + 1;
        }
        else
            /* largest = last + 1; */
            break;
    }
}

template<class T>
void heapsort(T data[], int size)
{
    /* 建堆 ,从最后一个节点的父节点开始向下减, 因为这些节点才可能向下移动 */
    for(int i = size/2 - 1; i >= 0; --i)
    {
        moveDown(data, i, size-1);
    }
    for(int i = size - 1; i >= 1; --i)
    {
        /* 把最大的值从后面开始交换 */
        swap(data[0], data[i]);
        moveDown(data, 0, i-1);
    }
}


template<class T>
int Partition(T data[], int length, int start, int end)
{
    int bound = data[end];
    int small = start - 1;
    for(int i = start; i < end; ++i)
    {
        if(data[i] < data[end])
        {
            ++small;
            if(small != i)
            {
                swap(data[i], data[small]);
            }
        }
    }

    ++small;
    swap(data[small], data[end]);

    return small;
}

template<class T>
void QuickSort(T data[], int length, int start, int end)
{
    if(start == end)
        return;

    int index = Partition(data, length, start, end);
    if(index > start)
        QuickSort(data, length, start, index-1);
    if(index < end)
        QuickSort(data, length, index+1, end);
}


template<class T>
void quicksort(T data[], int first, int last)
{
    int lower = first, upper = last;
    /* 选取中间的值为边界值，并与第一个值交换位置 */
    /* swap(data[first], data[(first+last)/2]); */
    T bound = data[first];

    while(lower < upper)
    {
        while(lower < upper && data[upper] > bound)
            upper--;

        if(lower < upper)
            data[lower++] = data[upper];

        while(lower < upper && data[lower] < bound)
            lower++;

        if(lower < upper)
            data[upper--] = data[lower];
    }

    /* 将边界值放入最终的位置 */
    /* swap(data[first], data[upper]); */
    data[lower] = bound;
    if(first < upper-1)
        quicksort(data, first, upper-1);
    if(upper+1 < last)
        quicksort(data, upper+1, last);
}

template<class T>
void quicksort(T data[], int n)
{
    /* int max; */
    if(n < 2)
        return;
    /* 找到最大的数 */
    /* for(int i = 0; i < n-1; i++) */
    /* { */
    /*     if(data[i] > data[i+1]) */
    /*         max = i; */
    /* } */
    /* 把最大的数放到最后 */
    /* 防止lower的值超过数组的末端 */
    /* 如果边界是数组的最大元素，在第一层内层循环中就可能出现上述情况： */
    /* 索引lower的值会不断增长，直至使程序非正常中断 */
    /* swap(data[max], data[n-1]); */
    /* 由于最后一个数已经确定是最大的，所以last设为倒数第二个 */
    quicksort(data, 0, n-1);
}


template<class T>
void merge(T data[], int first, int last)
{
    int mid = (first + last) / 2;
    int i1 = 0, i2 = first, i3 = mid+1;
    const int n = last;
    /* 要申请额外的空间 */
    T temp[n];
    while(i2 <= mid && i3 <= last)
    {
        if(data[i2] < data[i3])
            temp[i1++] = data[i2++];
        else
            temp[i1++] = data[i3++];
    }

    while(i2 <= mid)
        temp[i1++] = data[i2++];
    while(i3 <= last)
        temp[i1++] = data[i3++];

    for(int i = 0; i < i1; i++)
        data[first+i] = temp[i];
}

template<class T>
void mergesort(T data[], int first, int last)
{
    if(first < last)
    {
        int mid = (first + last) / 2;
        mergesort(data, first, mid);
        mergesort(data, mid+1, last);
        merge(data, first, last);
    }
}


int main()
{
    int data[num];
    init(data);
    /* cout << "before:" << endl; */
    /* print(data); */
    clock_t start, end;
    start = clock();
    /* quicksort(data, num); */
    QuickSort(data, num, 0, num-1);
    end = clock();
    cout << "quicksort: " << endl;
    printf("%ld\n", (end - start));
    cout << endl;
    /* cout << "after:" << endl; */
    /* print(data); */

    init(data);
    /* cout << "before:" << endl; */
    /* print(data); */
    start = clock();
    insertionsort(data, num);
    end = clock();
    cout << "insertionsort: " << endl;
    printf("%ld\n", (end - start));
    cout << endl;
    /* print(data); */


    init(data);
    start = clock();
    selectsort(data, num);
    end = clock();
    cout << "selectsort: " << endl;
    printf("%ld\n", (end - start));
    cout << endl;


    init(data);
    start = clock();
    shellsort(data, num);
    end = clock();
    cout << "shellsort: " << endl;
    printf("%ld\n", (end - start));
    cout << endl;


    init(data);
    /* cout << "before:" << endl; */
    /* print(data); */
    start = clock();
    heapsort(data, num);
    end = clock();
    cout << "heapsort: " << endl;
    printf("%ld\n", (end - start));
    cout << endl;
    /* print(data); */


    init(data);
    start = clock();
    bubblesort(data, num);
    end = clock();
    cout << "bubblesort: " << endl;
    printf("%ld\n", (end - start));
    cout << endl;


    init(data);
    /* cout << "before:" << endl; */
    /* print(data); */
    start = clock();
    mergesort(data, 0, num-1);
    end = clock();
    cout << "mergesort: " << endl;
    printf("%ld\n", (end - start));
    cout << endl;
    /* print(data); */


    return 0;
}