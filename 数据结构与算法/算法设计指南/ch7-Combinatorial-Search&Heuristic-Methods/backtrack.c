#include "backtrack.h"
#include "bool.h"

bool finished = FALSE;                  /* found all solutions yet? */

void backtrack(int a[], int k, data input)
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
