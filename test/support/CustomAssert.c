#include "unity.h"
#include "CustomAssert.h"

void assertEqualPerson(Person *expected, Person *actual, int line, char *msg){
	UNITY_TEST_ASSERT_EQUAL_STRING(expected->name, actual->name, line, "Not the same Name.");
	UNITY_TEST_ASSERT_EQUAL_INT(expected->age, actual->age, line, "Not the same Age.");
	UNITY_TEST_ASSERT_FLOAT_WITHIN(0.0001,expected->weight, actual->weight, line, "Not the same Weight.");
	
}


void assertEqualPERSON(char *expectedName, int expectedAge, float expectedWeight, Person *actual, int line, char *msg){

	UNITY_TEST_ASSERT_EQUAL_STRING(expectedName, actual->name, line, "Not the same Name.");
	UNITY_TEST_ASSERT_EQUAL_INT(expectedAge, actual->age, line, "Not the same Age.");
	UNITY_TEST_ASSERT_FLOAT_WITHIN(0.0001,expectedWeight, actual->weight, line, "Not the same Weight.");
	
}