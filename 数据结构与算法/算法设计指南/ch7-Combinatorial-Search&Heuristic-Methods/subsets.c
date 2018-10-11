#include "bool.h"
#include "backtrack.h"
#include <stdio.h>

void process_solution(int a[], int k)
{
    int i;				/* counter */

    printf("{");
    for (i=1; i<=k; i++)
        if (a[i] == TRUE) printf(" %d",i);

    printf(" }\n");
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

/* What are possible elements of the next slot in the permutation?  */

void construct_candidates(int a[], int k, int n, int c[], int *ncandidates)
{
    c[0] = TRUE;
    c[1] = FALSE;
    *ncandidates = 2;
}

int main()
{
    int a[NMAX];    /* solution vector */

    backtrack(a, 0, 3);

    return 0;
}
