#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"
#include <sys/time.h>


long timeval_diff(struct timeval *t2, struct timeval *t1) { 
  long diff = (t2->tv_usec + 1000000 * t2->tv_sec) - (t1->tv_usec + 1000000 * t1->tv_sec); 
  return (diff);
} 


int main(){


  struct timeval tvStart1, tvEnd1, tvStart2, tvEnd2, tvStart3, tvEnd3, tvStart4, tvEnd4 ;
  gettimeofday(&tvStart1, NULL);
  int *mymall = (int *)mymalloc(100*sizeof(int));
  long *mymall2 = (long *)mymalloc(10*sizeof(long));
  gettimeofday(&tvEnd1, NULL);
  gettimeofday(&tvStart2, NULL);
  int *mall = (int *)malloc(100*sizeof(int));
  long *mall2 = (long *)malloc(10*sizeof(long));
  gettimeofday(&tvEnd2, NULL);
  printf("Duration mymalloc : %ld microseconds\nDuration malloc : %ld microseconds\n", timeval_diff(&tvEnd1, &tvStart1), timeval_diff(&tvEnd2, &tvStart2));
  gettimeofday(&tvStart3, NULL);
  int *mycall = (int *)mycalloc(100*sizeof(int));
  long *mycall2 = (long *)mycalloc(10*sizeof(long));
  gettimeofday(&tvEnd3, NULL);
  gettimeofday(&tvStart4, NULL);
  int *call = (int *)calloc(100*sizeof(int));
  long *call2 = (long *)calloc(10*sizeof(long));
  gettimeofday(&tvEnd4, NULL);
  printf("Duration mycalloc : %ld microseconds\nDuration calloc : %ld microseconds\n", timeval_diff(&tvEnd3, &tvStart3), timeval_diff(&tvEnd4, &tvStart4));
}
