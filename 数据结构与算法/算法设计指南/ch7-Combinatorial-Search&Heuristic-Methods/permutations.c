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

