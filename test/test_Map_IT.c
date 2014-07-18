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
#define getPersonFromBucketLinear(x) ((Person *)(x))

void setUp(void){}
void tearDown(void){}

void test_mapNew_given_length_of_10_should_create_a_new_Map(void){
	Map *map = mapNew(10);
	
	TEST_ASSERT_NOT_NULL(map);
	TEST_ASSERT_NOT_NULL(map->bucket);
	TEST_ASSERT_EQUAL(10,map->length);
	TEST_ASSERT_EQUAL(0,map->size);
	
}
///////////////////
//   MAP ADD     //
///////////////////

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
  
  // TEST_ASSERT_EQUAL_PERSON("Ali",25,70.3,getPersonFromBucket(map->bucket[3]));
	
}
void test_mapStore_given_Ali_but_Ali_is_same_in_Map(){
	CEXCEPTION_T e;
	Person *person = personNew("Ali",25,70.3);
	List *list = listNew(person, NULL);
	Map *map = mapNew(5);
	
	map->bucket[3] =list;
	hash_ExpectAndReturn(person,3);
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
	hash_ExpectAndReturn(Zorro,3);
	
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
void test_mapFind_given_Ali_and_ali_is_in_the_Map_should_return_Ali_object1(){
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
void test_mapFind_given_Ali_and_ali_is_not_in_the_Map_should_return_NULL_since_no_Ali_object_in_Map2(){
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
void test_mapFind_given_Ali_and_ali_is_in_the_linkedList_in_the_map_should_return_Ali_object3(){
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
void test_mapFind_given_Ali_and_ali_is_not_in_the_linkedList_in_the_map_should_return_NULL4(){
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
////////////////////
//   MAP REMOVE   //
////////////////////
void test_mapRemove_given_Ali_and_ali_is_in_the_Map_should_return_Ali_object1(){
  Person *Ali = personNew("Ali",25,70.3);
  List *list = listNew(Ali, NULL);
  Map *map = mapNew(5);
  Person *person;
	
	map->bucket[3] = list;
  hash_ExpectAndReturn(Ali,3);
  
  person = mapRemove(map , Ali ,comparePerson, hash);
  
  // listDump(list, personDump);
  
  TEST_ASSERT_NULL(person);
  TEST_ASSERT_NULL(getPersonFromBucket(map->bucket[3]));
}
void test_mapRemove_given_Ali_and_ali_is_not_in_the_Map_should_return_NULL_since_no_Ali_object_in_Map2(){
  Person *Ali = personNew("Ali",25,70.3);
  List *list = listNew(Ali, NULL);
  Map *map = mapNew(5);
  Person *person;
	
	// map->bucket[3] = list; // no add
  hash_ExpectAndReturn(Ali,3);
  comparePerson(Ali,Ali);
  
  person = mapRemove(map , Ali ,comparePerson, hash);
  
  TEST_ASSERT_NULL(map->bucket[3]);
  TEST_ASSERT_NULL(person);
}
void test_mapRemove_given_Ali_and_ali_is_in_the_linkedList_in_the_map_should_return_Ali_object3(){
  Person *Ali = personNew("Ali",25,70.3);
  Person *Zorro = personNew("Zorro",60,55.4);
  Person *person;
  
  List *list = listNew(Ali, NULL);
  list = listAdd(Zorro,list);
  
  Map *map = mapNew(5);
  map->bucket[3] = list;
  hash_ExpectAndReturn(Zorro,3);
  
  // listDump(list, personDump);
  
  person = mapRemove(map , Zorro ,comparePerson, hash);
  
  // listDump(list, personDump);
  
  TEST_ASSERT_NULL(person);
  TEST_ASSERT_NULL(getPersonFromBucket(map->bucket[3]));
  TEST_ASSERT_NOT_NULL(getPersonFromBucket(((List *)map->bucket[3])->next));
  TEST_ASSERT_EQUAL_Person(Ali,getPersonFromBucket(((List *)map->bucket[3])->next));
  
}
void test_mapRemove_given_Ali_and_ali_is_not_in_the_linkedList_in_the_map_should_return_NULL4(){
  Person *Ali = personNew("Ali",25,70.3);
  Person *Zorro = personNew("Zorro",60,55.4);
  Person *Kikuri = personNew("Kikuri",50,40.4);
  Person *person;

  List *list = listNew(Kikuri, NULL);
  list = listAdd(Zorro,list);
  
  Map *map = mapNew(5);
  map->bucket[3] = list;
  hash_ExpectAndReturn(Ali,3);
  
  // listDump(list, personDump);
  
  person = mapRemove(map , Ali ,comparePerson, hash);
  
  // listDump(list, personDump);
  
  TEST_ASSERT_NULL(person);
  TEST_ASSERT_NOT_NULL(getPersonFromBucket(map->bucket[3]));
}
void test_mapRemove_given_Ali_and_ali_is_in_the_list_of_3_element_in_the_map_and_should_remove_Ali_and_return_it_to_caller(){
  Person *Ali = personNew("Ali",25,70.3);
  Person *Zorro = personNew("Zorro",60,55.4);
  Person *Kikuri = personNew("Kikuri",48,46.4);
  Person *person;

  List *list = listNew(Ali, NULL);
  list = listAdd(Zorro,list);
  list = listAdd(Kikuri,list);
  
  Map *map = mapNew(5);
  map->bucket[3] = list;
  hash_ExpectAndReturn(Kikuri,3);
  
  // listDump(list, personDump);
  
  person = mapRemove(map , Kikuri ,comparePerson, hash);
  
  // listDump(list, personDump);
  
  TEST_ASSERT_NULL(person);
  TEST_ASSERT_NULL(getPersonFromBucket(map->bucket[3]));
  TEST_ASSERT_NOT_NULL(getPersonFromBucket(((List *)map->bucket[3])->next));
  TEST_ASSERT_NOT_NULL(getPersonFromBucket(((List *)map->bucket[3])->next->next));
  TEST_ASSERT_EQUAL_Person(Zorro,getPersonFromBucket(((List *)map->bucket[3])->next));
  TEST_ASSERT_EQUAL_Person(Ali,getPersonFromBucket(((List *)map->bucket[3])->next->next));
}

////////////////////////
//   MAP LINEAR ADD   //
////////////////////////

void test_maplinearStore_given_Ali_and_Zorro_should_add_to_the_next_bucket(){
	CEXCEPTION_T e;
	Person *Ali = personNew("Ali",25,70.3);
	Person *Zorro = personNew("Zorro",60,55.4);
	Map *map = mapNew(5);
	
	map->bucket[3] = Ali;
	hash_ExpectAndReturn(Zorro,3);
	// comparePerson(Ali,Zorro);
	
	Try{
		maplinearStore(map , Zorro ,comparePerson, hash);

		TEST_ASSERT_NOT_NULL(map->bucket[3]);
		TEST_ASSERT_NOT_NULL(map->bucket[4]);
		TEST_ASSERT_EQUAL_Person(Ali,map->bucket[3]);
		TEST_ASSERT_EQUAL_Person(Zorro,map->bucket[4]);
		TEST_ASSERT_EQUAL_Person(Ali,getPersonFromBucketLinear(map->bucket[3]));
		TEST_ASSERT_EQUAL_Person(Zorro,getPersonFromBucketLinear(map->bucket[4]));
	}
	Catch(e){
		TEST_FAIL_MESSAGE("Expect Zorro");
	}
}
void test_maplinearStore_given_Ali_Zorro_and_Sefia_should_add_to_the_next_bucket(){
	CEXCEPTION_T e;
	Person *Ali = personNew("Ali",25,70.3);
	Person *Zorro = personNew("Zorro",60,55.4);
	Person *Sefia = personNew("Sefia",55,48.4);
	Map *map = mapNew(6);
	
	map->bucket[3] = Ali;
	map->bucket[4] = Zorro;
  
	hash_ExpectAndReturn(Sefia,3);
	
	Try{
		maplinearStore(map , Sefia ,comparePerson, hash);

		TEST_ASSERT_NOT_NULL(map->bucket[3]);
		TEST_ASSERT_NOT_NULL(map->bucket[4]);
		TEST_ASSERT_NOT_NULL(map->bucket[5]);
		TEST_ASSERT_EQUAL_Person(Ali,map->bucket[3]);
		TEST_ASSERT_EQUAL_Person(Zorro,map->bucket[4]);
		TEST_ASSERT_EQUAL_Person(Sefia,map->bucket[5]);
		TEST_ASSERT_EQUAL_Person(Ali,getPersonFromBucketLinear(map->bucket[3]));
		TEST_ASSERT_EQUAL_Person(Zorro,getPersonFromBucketLinear(map->bucket[4]));
		TEST_ASSERT_EQUAL_Person(Sefia,getPersonFromBucketLinear(map->bucket[5]));
	}
	Catch(e){
		TEST_FAIL_MESSAGE("Expect Sefia");
	}
}
void test_maplinearStore_given_Ali_Zorro_and_Sefia_should_add_to_the_next_bucket_and_full_should_throw_error(){
	CEXCEPTION_T e;
	Person *Ali = personNew("Ali",25,70.3);
	Person *Zorro = personNew("Zorro",60,55.4);
	Person *Sefia = personNew("Sefia",55,48.4);
	Person *Kikuri = personNew("Kikuri",45,42.4);
	Map *map = mapNew(5);
	
	map->bucket[3] = Ali;
	map->bucket[4] = Zorro;
	map->bucket[5] = Sefia;
  
	hash_ExpectAndReturn(Kikuri,3);
	
	Try{
		maplinearStore(map , Kikuri ,comparePerson, hash);

		TEST_ASSERT_NOT_NULL(map->bucket[3]);
		TEST_ASSERT_NOT_NULL(map->bucket[4]);
		TEST_ASSERT_NOT_NULL(map->bucket[5]);
		TEST_ASSERT_EQUAL_Person(Ali,map->bucket[3]);
		TEST_ASSERT_EQUAL_Person(Zorro,map->bucket[4]);
		TEST_ASSERT_EQUAL_Person(Sefia,map->bucket[5]);
		TEST_ASSERT_EQUAL_Person(Ali,getPersonFromBucketLinear(map->bucket[3]));
		TEST_ASSERT_EQUAL_Person(Zorro,getPersonFromBucketLinear(map->bucket[4]));
		TEST_ASSERT_EQUAL_Person(Sefia,getPersonFromBucketLinear(map->bucket[5]));
	}
	Catch(e){
		TEST_FAIL_MESSAGE("Expect ERROR");
    TEST_ASSERT_EQUAL(ERROR, e);
    TEST_ASSERT_NULL(map->bucket[6]);
	}
}
void test_maplinearStore_given_Ali_but_Ali_is_same_in_Map(){
	CEXCEPTION_T e;
	Person *Ali = personNew("Ali",25,70.3);
	Map *map = mapNew(5);
	
	map->bucket[3] =Ali;
	hash_ExpectAndReturn(Ali,3);
	comparePerson(Ali,Ali);
	
	Try{
		maplinearStore(map , Ali ,comparePerson, hash);
		TEST_FAIL_MESSAGE("Expect ERR_SAME_ELEMENT");
	}
	Catch(e){
	TEST_ASSERT_EQUAL(ERR_SAME_ELEMENT, e);
	TEST_ASSERT_NOT_NULL(map->bucket[3]);
	TEST_ASSERT_EQUAL_Person(Ali,getPersonFromBucketLinear(map->bucket[3]));
	}
}
/////////////////////////
//   MAP LINEAR FIND   //
/////////////////////////
void test_maplinearFind_given_Ali_and_ali_is_in_the_Map_should_return_Ali_object1(){
  Person *Ali = personNew("Ali",25,70.3);
  Person *person;
	Map *map = mapNew(5);
	
	map->bucket[5] = Ali;
  hash_ExpectAndReturn(Ali,5);
  
  person =  maplinearFind(map , Ali ,comparePerson, hash);
  TEST_ASSERT_NOT_NULL(map->bucket[5]);
  TEST_ASSERT_EQUAL_Person(Ali,getPersonFromBucketLinear(map->bucket[5]));
  
}
void test_maplinearFind_given_Ali_and_ali_is_not_in_the_Map_should_return_NULL_since_no_Ali_object_in_Map2(){
  Person *Ali = personNew("Ali",25,70.3);
  Person *person;
	Map *map = mapNew(5);
	
	// map->bucket[5] = Ali; // no add
  hash_ExpectAndReturn(Ali,5);
  
  person = maplinearFind(map , Ali ,comparePerson, hash);

  TEST_ASSERT_NULL(person);
}
void test_maplinearFind_given_Ali_and_ali_is_in_the_linkedList_in_the_map_should_return_Ali_object3(){
  Person *Ali = personNew("Ali",25,70.3);
  Person *Zorro = personNew("Zorro",60,55.4);
  Person *person;
  
  Map *map = mapNew(5);
  map->bucket[3] = Ali;
  map->bucket[4] = Zorro;
  
  hash_ExpectAndReturn(Ali,3);
  
  person = maplinearFind(map , Ali ,comparePerson, hash);
  
  TEST_ASSERT_NOT_NULL(person);
  TEST_ASSERT_EQUAL_Person(Ali,person);
  
}
void test_maplinearFind_given_Ali_and_ali_is_not_in_the_linkedList_in_the_map_should_return_NULL4(){
  Person *Ali = personNew("Ali",25,70.3);
  Person *Zorro = personNew("Zorro",60,55.4);
  Person *Abu = personNew("Abu",60,55.4);
  Person *person;
  
  Map *map = mapNew(6);
  map->bucket[3] = Zorro;
  map->bucket[4] = Abu;
  
  hash_ExpectAndReturn(Ali,3);
  
  person = maplinearFind(map , Ali ,comparePerson, hash);
  
  TEST_ASSERT_NULL(person);
}
///////////////////////////
//   MAP LINEAR REMOVE   //
///////////////////////////
void test_maplinearRemove_given_Ali_and_ali_is_in_the_Map_should_return_Ali_object1(){
  Person *Ali = personNew("Ali",25,70.3);
  Map *map = mapNew(5);
  Person *person;
	
	map->bucket[3] = Ali;
  hash_ExpectAndReturn(Ali,3);
  
  person = maplinearRemove(map , Ali ,comparePerson, hash);
  
  TEST_ASSERT_NOT_NULL(person);
  TEST_ASSERT_EQUAL_Person(Ali,person);
  TEST_ASSERT_NULL(getPersonFromBucketLinear(map->bucket[3]));
  
}
void test_maplinearRemove_given_Ali_and_ali_is_not_in_the_Map_should_return_NULL_since_no_Ali_object_in_Map2(){
  Person *Ali = personNew("Ali",25,70.3);
  Map *map = mapNew(5);
  Person *person;
	
	// map->bucket[5] = Ali; // no add
  hash_ExpectAndReturn(Ali,3);
  comparePerson(Ali,Ali);
  
  person = maplinearRemove(map , Ali ,comparePerson, hash);
  
  TEST_ASSERT_NULL(map->bucket[3]);
  TEST_ASSERT_NULL(person);
  TEST_ASSERT_NULL(getPersonFromBucketLinear(map->bucket[3]));
}
void test_maplinearRemove_given_Ali_and_ali_is_in_the_linkedList_in_the_map_should_return_Ali_object3(){
  Person *Ali = personNew("Ali",25,70.3);
  Person *Zorro = personNew("Zorro",60,55.4);
  Person *person;
  
  Map *map = mapNew(5);
  map->bucket[3] = Ali;
  map->bucket[4] = Zorro;
  
  hash_ExpectAndReturn(Zorro,3);
  
  // personDump(map->bucket[3]);
  // personDump(map->bucket[4]);
  // personDump(map->bucket[5]);
  
  person = maplinearRemove(map , Zorro ,comparePerson, hash);
  
  // personDump(map->bucket[3]);
  // personDump(map->bucket[4]);
  // personDump(map->bucket[5]);
  
  TEST_ASSERT_NOT_NULL(person);
  TEST_ASSERT_EQUAL_Person(Zorro,person);
  TEST_ASSERT_NOT_NULL(getPersonFromBucketLinear(map->bucket[3]));
  TEST_ASSERT_EQUAL_Person(Ali,getPersonFromBucketLinear(map->bucket[3]));
  
}
void test_maplinearRemove_given_Ali_and_ali_is_not_in_the_linkedList_in_the_map_should_return_NULL4(){
  Person *Ali = personNew("Ali",25,70.3);
  Person *Zorro = personNew("Zorro",60,55.4);
  Person *Kikuri = personNew("Kikuri",50,40.4);
  Person *person;
  
  Map *map = mapNew(5);
  map->bucket[3] = Ali;
  map->bucket[4] = Zorro;
  hash_ExpectAndReturn(Kikuri,3);
  
  // personDump(map->bucket[3]);
  // personDump(map->bucket[4]);
  // personDump(map->bucket[5]);
  
  person = maplinearRemove(map , Kikuri ,comparePerson, hash);
  
  // personDump(map->bucket[3]);
  // personDump(map->bucket[4]);
  // personDump(map->bucket[5]);
  
  TEST_ASSERT_NULL(person);
  
  TEST_ASSERT_NOT_NULL(map->bucket[3]);
  TEST_ASSERT_NOT_NULL(map->bucket[4]);
  
  TEST_ASSERT_NOT_NULL(getPersonFromBucketLinear(map->bucket[3]));
  TEST_ASSERT_NOT_NULL(getPersonFromBucketLinear(map->bucket[4]));
  TEST_ASSERT_EQUAL_Person(Ali,getPersonFromBucketLinear(map->bucket[3]));
  TEST_ASSERT_EQUAL_Person(Zorro,getPersonFromBucketLinear(map->bucket[4]));
}
void test_maplinearRemove_given_Ali_and_ali_is_in_the_list_of_3_element_in_the_map_and_should_remove_Ali_and_return_it_to_caller(){
  Person *Ali = personNew("Ali",25,70.3);
  Person *Zorro = personNew("Zorro",60,55.4);
  Person *Kikuri = personNew("Kikuri",48,46.4);
  Person *person;
  
  Map *map = mapNew(6);
  map->bucket[3] = Ali;
  map->bucket[4] = Zorro;
  map->bucket[5] = Kikuri;
  
  hash_ExpectAndReturn(Kikuri,3);
  
  // personDump(map->bucket[3]);
  // personDump(map->bucket[4]);
  // personDump(map->bucket[5]);
  // printf("beforeremove\n");
  person = maplinearRemove(map , Kikuri ,comparePerson, hash);
  // printf("afterremove\n");
  // personDump(map->bucket[3]);
  // personDump(map->bucket[4]);
  // personDump(map->bucket[5]);
  
  TEST_ASSERT_NOT_NULL(person);
  TEST_ASSERT_NOT_NULL(map->bucket[3]);
  TEST_ASSERT_NOT_NULL(map->bucket[4]);
  TEST_ASSERT_NULL(map->bucket[5]);
  
  TEST_ASSERT_EQUAL_Person(Kikuri,person);
  
  TEST_ASSERT_EQUAL_Person(Ali,getPersonFromBucketLinear(map->bucket[3]));
  TEST_ASSERT_EQUAL_Person(Zorro,getPersonFromBucketLinear(map->bucket[4]));
}