#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"
#include <CUnit/CUnit.h>
#include <CUnit/TestRun.h>

//test 1, le int se remet-il a la bonne place?
void test1(void){
  long *a = (long *)mymalloc(sizeof(long));
  int *b = (int *)mymalloc(sizeof(int));
  long *c = (long *)mymalloc(sizeof(long));
  myfree(b);
  int *d =(int *)mymalloc(sizeof(int));
  myfree(a);
  myfree(c);
  myfree(d);
  CU_ASSERT_PTR_EQUAL(d, b);
}

//espace memoire insuffisant lors d'un appel à malloc
 void test2(void){
  char *ptr = (char *) mymalloc(92);
  long *ptr2 = (long *)mymalloc(sizeof(long));
  printf("pointeur 1:%p, pointeur 2: %p\n", ptr,ptr2);
  myfree(ptr);
  CU_ASSERT_PTR_NULL(ptr2);
 }
 
//regarde si mycalloc remet tout a zero
void test3(void){
  printf("enter test 3\n");
  int check = 0;
  char *a =(char *)mycalloc(10*(sizeof(char)));
  char *b = a;
  printf("malloc OK\n");
  int i = 0;
  while(i<10){
    if(*(b+i) != 0){
      printf("not equal to 0\n");
      check = 1;
    }
    printf("adresse : %p", (char *)(b+i));
    printf("%d\n", i);
    i++;
  }
  //myfree(a);
  CU_ASSERT_FALSE(check);
}

//test de myfree ou verifie si un block se dessalloue correctement
void test4(void){
char *ptr = (char *) mymalloc(sizeof(int));
int a = ptr;
myfree(ptr);
char *ptr2 = (char *) mymalloc(sizeof(int));
int b = ptr2;
myfree(ptr2);
int heyyy = b - a;
CU_ASSERT_FALSE(heyyy);
}

//test la fragmentation interne ou vérification du respect de l'alignement des blocs
void test5(void){
  printf("test 5\n");
char *ptr = (char *) mymalloc(1);
char *ptr2 = (char *) mymalloc(1);
int hey = ptr + 8 - ptr2;
myfree(ptr);
myfree(ptr2);
CU_ASSERT_FALSE(hey);
}

//test la fragmentation externe
/*void test6(void){
printf("test 6");
char *ptr = (char *) mymalloc(sizeof(long));
char *ptr2 = (char *) mymalloc(sizeof(int));
char *ptr3 = (char *) mymalloc(sizeof(long));
myfree(ptr2);
char *ptr4 = (char *) mymalloc(sizeof(long));
char *ptr5 = (char *) mymalloc(sizeof(int));
int hey = ptr + 8 - ptr5;
int yo = ptr3 + 12 - ptr4;
int salut = hey - yo;
myfree(ptr);
myfree(ptr3);
myfree(ptr4);
myfree(ptr5);
CU_ASSERT_FALSE(salut);
}
*/


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
  (NULL == CU_add_test(pSuite, "Test 4",test4))|| 
  (NULL == CU_add_test(pSuite, "Test 5", test5))/*||
  (NULL == CU_add_test(pSuite, "Test 6",test6))*/){
    CU_cleanup_registry();
    return CU_get_error();
  }
  CU_basic_run_tests();
  CU_basic_show_failures(CU_get_failure_list());
}
