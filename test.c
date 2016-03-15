#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"
#include "CUnit.h"
//test 1, le int se remet-il a la bonne place?
void test1(void){
  long *a = mymalloc(sizeof(int));
  int *b = mymalloc(sizeof(int));
  long *c = mymalloc(sizeof(long));
  myfree(b);
  int *d = mymalloc(sizeof(int));
  CU_ASSERT_PTR_EQUAL(d, b);
}

void test2(void){
  char *a = mymalloc(-1);
  CU_ASSERT_PTR_NULL(a);
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
