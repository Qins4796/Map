#include "unity.h"
#include "Map.h"
#include "Person.h"
// #include "mock_ComparePerson.h"
#include "ComparePerson.h"
#include "mock_Hash.h"
#include "List.h"
#include "CustomAssert.h"
#include "ErrorCode.h"
#include "CException.h"

#define getPersonFromBucket(x) ((Person *)((List *)(x))->data)

void setUp(void){}
void tearDown(void){}

void test_mapNew_given_length_of_10_should_create_a_new_Map(void){
	Map *map = mapNew(10);
	
	TEST_ASSERT_NOT_NULL(map);
	TEST_ASSERT_NOT_NULL(map->bucket);
	TEST_ASSERT_EQUAL(10,map->length);
	TEST_ASSERT_EQUAL(0,map->size);
	
}
/**	
	Add Ali into an empty map. Ali is first hashed and hash value 3 is obtained and then placed into bucket 3;
*/
void test_mapStore_given_Ali_should_add_it_to_map(void){
	Person *person = personNew("Ali",25,70.3);
	Map *map = mapNew(5);
	
	hash_ExpectAndReturn(person,3);
	
	mapStore(map, person, comparePerson, hash);
	TEST_ASSERT_NOT_NULL(map->bucket[3]);
	TEST_ASSERT_EQUAL_STRING("Ali",((Person *)((List *)map->bucket[3])->data)->name);
	TEST_ASSERT_EQUAL_Person(person,(Person *)((List *)map->bucket[3])->data);
	
	TEST_ASSERT_EQUAL_Person(person,getPersonFromBucket(map->bucket[3]));
	
}
void test_mapStore_given_Ali_but_Ali_is_same_in_Map(){
	CEXCEPTION_T e;
	Person *person = personNew("Ali",25,70.3);
	List *list = listNew(person, NULL);
	Map *map = mapNew(5);
	
	map->bucket[3] =list;
	hash_ExpectAndReturn(person,3);
	// comparePerson_ExpectAndReturn(person,person,1);
	comparePerson(person,person);
	
	Try{
		mapStore(map , person ,comparePerson, hash);
		TEST_FAIL_MESSAGE("Expect ERR_SAME_ELEMENT");
	}
	Catch(e){
	TEST_ASSERT_EQUAL(ERR_SAME_ELEMENT, e);
	TEST_ASSERT_NOT_NULL(map->bucket[3]);
	TEST_ASSERT_EQUAL_Person(person,getPersonFromBucket(map->bucket[3]));
	}
}
void test_mapStore_given_Zorro_added_into_Ali_in_the_Map(){
	CEXCEPTION_T e;
	Person *person = personNew("Ali",25,70.3);
	Person *Zorro = personNew("Zorro",60,55.4);
	List *list = listNew(person, NULL);
	Map *map = mapNew(5);
	
	map->bucket[3] = list;
	// hash_ExpectAndReturn(person,3);
	// comparePerson_ExpectAndReturn(person,person,1);
	hash_ExpectAndReturn(Zorro,3);
	// comparePerson_ExpectAndReturn(person,Zorro,0);
	comparePerson(person,Zorro);
	
	Try{
		mapStore(map , Zorro ,comparePerson, hash);

		TEST_ASSERT_NOT_NULL(map->bucket[3]);
		TEST_ASSERT_EQUAL_Person(Zorro,getPersonFromBucket(map->bucket[3]));
		TEST_ASSERT_EQUAL_Person(person,getPersonFromBucket(((List *)map->bucket[3])->next));
	}
	Catch(e){
		TEST_FAIL_MESSAGE("Expect Zorro");
	}
}
///////////////////
//   MAP FIND    //
///////////////////
void test_given_Ali_and_ali_is_in_the_Map_should_return_Ali_object1(){
  Person *Ali = personNew("Ali",25,70.3);
  Person *person;
  List *list = listNew(Ali, NULL);
	Map *map = mapNew(5);
	
	map->bucket[5] = list;
  hash_ExpectAndReturn(Ali,5);
  // comparePerson(Ali,Ali);
  
  person =  mapFind(map , Ali ,comparePerson, hash);
  TEST_ASSERT_NOT_NULL(map->bucket[5]);
  TEST_ASSERT_EQUAL_Person(Ali,getPersonFromBucket(map->bucket[5]));
  
}
void test_given_Ali_and_ali_is_not_in_the_Map_should_return_NULL_since_no_Ali_object_in_Map2(){
  Person *Ali = personNew("Ali",25,70.3);
  Person *person;
  List *list = listNew(Ali, NULL);
	Map *map = mapNew(5);
	
	// map->bucket[5] = list; // no add
  hash_ExpectAndReturn(Ali,5);
  // comparePerson(Ali,Ali);
  
  person = mapFind(map , Ali ,comparePerson, hash);

  TEST_ASSERT_NULL(person);
}
void test_given_Ali_and_ali_is_in_the_linkedList_in_the_map_should_return_Ali_object3(){
  Person *Ali = personNew("Ali",25,70.3);
	Person *Zorro = personNew("Zorro",60,55.4);
  Person *person;
  
  List *list = listNew(Ali, NULL);
  list = listAdd(Zorro,list);
  
  Map *map = mapNew(5);
  map->bucket[5] = list;
  hash_ExpectAndReturn(Ali,5);
  
  person = mapFind(map , Ali ,comparePerson, hash);
  
  TEST_ASSERT_NOT_NULL(person);
  TEST_ASSERT_EQUAL_Person(Ali,person);
  
}
void test_given_Ali_and_ali_is_not_in_the_linkedList_in_the_map_should_return_NULL4(){
  Person *Ali = personNew("Ali",25,70.3);
	Person *Zorro = personNew("Zorro",60,55.4);
	Person *Abu = personNew("Abu",60,55.4);
  Person *person;
  
  List *list = listNew(Abu, NULL);
  list = listAdd(Zorro,list);
  
  Map *map = mapNew(5);
  map->bucket[5] = list;
  hash_ExpectAndReturn(Ali,5);
  
  person = mapFind(map , Ali ,comparePerson, hash);
  
  TEST_ASSERT_NULL(person);
}
