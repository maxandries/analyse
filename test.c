#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"
#include <sys/time.h>


long timeval_diff(struct timeval *t2, struct timeval *t1) { 
  long diff = (t2->tv_usec + 1000000 * t2->tv_sec) - (t1->tv_usec + 1000000 * t1->tv_sec); 
  return (diff);
} 


int main(){
  
}
