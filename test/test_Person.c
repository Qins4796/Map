#include "unity.h"
#include "Person.h"

void setUp(void){}
void tearDown(void){}

void test_personDump_explore(void){
	Person *person = personNew("Ali",23,64.8);
	
	// personDump(person);
}

void test_personNew_given_Ali_23_64_should_create_the_Person(void){
	Person *person = personNew("Ali",23,64.1);
	
	TEST_ASSERT_NOT_NULL(person);
	TEST_ASSERT_EQUAL_STRING("Ali", person->name);
	TEST_ASSERT_EQUAL(23, person->age);
	TEST_ASSERT_FLOAT_WITHIN(0.0001,64.1, person->weight);
}
