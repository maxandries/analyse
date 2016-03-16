#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"
#include <sys/time.h>


long timeval_diff(struct timeval *t2, struct timeval *t1) { 
  long diff = (t2->tv_usec + 1000000 * t2->tv_sec) - (t1->tv_usec + 1000000 * t1->tv_sec); 
  return (diff);
} 


int main(){


  struct timeval tvStart1, tvEnd1, tvStart2, tvEnd2;
  int i;
  gettimeofday(&tvStart1, NULL);
  int *mymall = (int *)mymalloc(100*sizeof(int));
  long *mymall2 = (long *)mymalloc(10*sizeof(long));
  gettimeofday(&tvEnd1, NULL);
  printf("adresse 1: %p\n adresse 2 : %p\n",mymall, mymall2);
  gettimeofday(&tvStart2, NULL);
  int *mall = (int *)malloc(100*sizeof(int));
  long *mall2 = (long *)malloc(10*sizeof(long));
  gettimeofday(&tvEnd2, NULL);
  printf("adresse 1: %p\n adresse 2 : %p\n",mall, mall2);
  printf("Duration mymalloc : %ld microseconds\nDuration malloc : %ld\n", timeval_diff(&tvEnd1, &tvStart1), timeval_diff(&tvEnd2, &tvStart2));
}
