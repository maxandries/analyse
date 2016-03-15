#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"
#include "CUnit.h"

void test1(void){
  long *a = mymalloc(sizeof(int));
  int *b = mymalloc(sizeof(int));
  long 
}

int main(){
  if (CUE_SUCCESS != CU_initialize_registry()) 
    return CU_get_error();
  int setup(void){
    return 0; 
  } 
  int teardown(void) { 
    return 0; 
  } // ... 
  CU_pSuite pSuite = NULL; // ... 
  pSuite = CU_add_suite("ma_suite", setup, teardown);
  if (NULL == pSuite) {
    CU_cleanup_registry(); 
    return CU_get_error(); 
  } 
}
