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
  int *mymall = (int *)mymalloc(sizeof(int));
  gettimeofday(&tvEnd1, NULL);
  gettimeofday(&tvStart2, NULL);
  int *mall = (int *)malloc(sizeof(int));
  gettimeofday(&tvEnd2, NULL);
  
  printf("Duration mymalloc : %ld microseconds\nDuration malloc : %ld\n", timeval_diff(&tvEnd1, &tvStart1), timeval_diff(&tvEnd2, &tvStart2));
}
