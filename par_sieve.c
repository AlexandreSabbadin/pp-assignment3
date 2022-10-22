#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <omp.h>

#define DEBUG 0        /* Set to 1 if you want a lot of output */
#define NR(i) (2*i+3)  /* The number represented by position i */
#define POS(k) (k/2-1)   /* The position in the array of number k */

#define K(offset,id,p,n) (offset+id*(n-offset)/p)

int main (int argc, char *argv[]) {
  int i, k, t, offset, N, N_pos, nr_primes, lastprime=0;
  int tid, nthreads;
  char *prime=NULL;
  const char unmarked = (char)0;
  const char marked = (char)1;
  clock_t start, stop;

  if (argc < 3) {
    printf("Usage:  %s nthreads N\n", argv[0]);
    exit(-1);
  }

  N = atoi(argv[2]);
  nthreads = atoi(argv[1]);

  /* To store the marks from 3 to N we need (N-3)/2+1 positions */
  N_pos = (N-3)/2+1;

  /* Allocate marks for all odd integers from 3 to N */
  prime = malloc(N_pos); 
  if (prime == NULL) {
    printf("Could not allocate %d chars of memory\n", N_pos);
    exit(-1);
  }

  /* Initialize all odd numbers to unmarked */
  for (i=0; i<N_pos; i++)
    prime[i] = unmarked;

#pragma omp parallel shared(prime,nthreads) private(i,t,k,tid) num_threads(nthreads)
  {
    tid = omp_get_thread_num();
    if (tid == 0) {
      printf("Starting with %d threads\n",nthreads);
    }
    
    for (i=0; NR(i) <= (int)sqrt((double)N); i++) {
      if (prime[i]==unmarked) {   /* Next unmarked position */
        t = NR(i);  /* Position i corresponds to the value t */
        //printf("[%d] %d\n", tid, t);
        offset = POS(t*t);
        k=K(offset,tid,nthreads,N_pos);
        while (NR(k)%t > 0) {
          k++;
        }
        for (k; k<K(offset,tid+1,nthreads,N_pos); k+=t) {
          //printf("\t[%d] %d %d\n", tid, k, NR(k));
          prime[k] = marked;  /* Mark the multiples of i */
        }
      }
    }


  }
  printf("2 ");
  int j;
  for (j=0; j<N_pos; j++) {
    if (prime[j] == unmarked) printf("%d ", NR(j));
  }
  printf("\n");

}