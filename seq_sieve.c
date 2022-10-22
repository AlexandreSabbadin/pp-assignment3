/*
  Improved Sieve of Erathostenes. Marks for even numbers are not stored.
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
 
#define DEBUG 0        /* Set to 1 if you want a lot of output */
#define NR(i) (2*i+1)  /* The number represented by position i */
#define POS(k) (k/2)   /* The position in the array of number k */

int main (int argc, char *argv[]) {
  int i, k, t, N, N_pos, nr_primes, lastprime=0;
  char *prime=NULL;
  const char unmarked = (char)0;
  const char marked = (char)1;
  clock_t start, stop;
  
  if (argc < 2) {
    printf("Usage:  %s N\n", argv[0]);
    exit(-1);
  }
  N = atoi(argv[1]);
  /* To store the marks from 3 to N we need (N-3)/2+1 positions */
  N_pos = (N-3)/2+1;

  start= clock();   /* Start measuring time */
  /* Allocate marks for all odd integers from 3 to N */
  prime = malloc(N_pos); 
  if (prime == NULL) {
    printf("Could not allocate %d chars of memory\n", N_pos);
    exit(-1);
  }

  /* Mark primes[0] since that is not used */
  prime[0] = marked;
  /* Initialize all odd numbers to unmarked */
  for (i=1; i<N_pos; i++)
    prime[i] = unmarked;

  /*Position i in the array prime now corresponds to the number 2*i+1 */
  for (i=1; NR(i) <= (int)sqrt((double)N); i++) {
    if (prime[i]==unmarked) {   /* Next unmarked position */
      if (DEBUG) printf("Marking multiples of %d: ", NR(i));
      t = NR(i);  /* Position i corresponds to the value t */
      for (k=POS(t*t); k<=N_pos; k+=NR(i)) {
        prime[k] = marked;  /* Mark the multiples of i */
        if (DEBUG) printf("%d ", NR(k));
      }
      if (DEBUG) printf("\n");
    }
  }
  
  nr_primes = 1;  /* Remember to count 2 as a prime */
  /* Count the marked numbers */
  for (i=1; i<=N_pos; i++) {
    if (prime[i]==unmarked) {
      lastprime = NR(i);
      nr_primes++;
    }
  }
  
  stop = clock();
  printf("Time: %6.1f s\n", (float)(stop-start)/CLOCKS_PER_SEC);

  if (DEBUG) {
    printf("\nPrime numbers smaller than or equal to %d are\n", N);
    printf("%d ", 2);     /* Remember to print the value 2 */
    for (i=1; i<=N_pos; i++) {
      if (prime[i]==unmarked) {
	printf("%d ",NR(i));
      }
    }
  }

  printf("\n%d primes smaller than or equal to %d\n", nr_primes, N);
  printf("The largest of these primes is %d\n", lastprime);
  printf("\nReady\n");

  exit(0);
}
