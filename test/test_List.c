#include "unity.h"
// #include "Person.h"
#include "List.h"

void setUp(void){}
void tearDown(void){}

void test_List_given_integer_5_should_create_an_empty_List(void){
	List *list;
	int int5 = 5;
	int *ptrInt;
	
	list = listNew(&int5,NULL);
	TEST_ASSERT_NOT_NULL(list);
	ptrInt = (int *)list->data;
	// TEST_ASSERT_EQUAL(5, *(int *)list->data);
	TEST_ASSERT_EQUAL(5, *ptrInt);
}
