#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"
#include <CUnit/CUnit.h>
#include <CUnit/TestRun.h>
//test 1, le int se remet-il a la bonne place?
void test1(void){
  long *a = (long *)mymalloc(sizeof(int));
  int *b = (int *)mymalloc(sizeof(int));
  long *c = (long *)mymalloc(sizeof(long));
  myfree(b);
  int *d =(int *)mymalloc(sizeof(int));
  CU_ASSERT_PTR_EQUAL(d, b);
}
//une taille negative retourne NULL
void test2(void){
  char *a = mymalloc(-1);
  printf("adresse test 2 :%p\n",a);
  CU_ASSERT_PTR_NULL(a);
}
//regarde si mycalloc remet tout a zero
void test3(void){
  int check = 0;
  char *a = mycalloc(10*(sizeof(char)));
  int i = 0;
  while(i<10){
    if(*(a+i) != 0){
      check = 1;
    }
    i++;
  }
  CU_ASSERT_FALSE(check);
}
//verifie si un block se dessalloue correctement
void test4(void){
  char *a = mymalloc(sizeof(char));
  myfree(a);
  CU_ASSERT_FALSE(((struct block_header *)(a-4))->alloc);
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
  if ((NULL == CU_add_test(pSuite, "Test 1", test1)) || 
  (NULL == CU_add_test(pSuite, "Test 2", test2)) || 
  (NULL == CU_add_test(pSuite, "Test 3", test3)) || 
  (NULL == CU_add_test(pSuite, "Test 4",test4))){
    CU_cleanup_registry();
    return CU_get_error();
  }
  CU_basic_run_tests();
  CU_basic_show_failures(CU_get_failure_list());
}
