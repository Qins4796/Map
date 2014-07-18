#include "Map.h"
#include "List.h"
#include "Person.h"
#include <stdio.h>
#include <malloc.h>
#include "ErrorCode.h"
#include "CException.h"

// unsigned int hashValue = 0;
// void *currentBucket = map->bucket[hashValue];
// if (isBucketEmpty(currentBucket)){store}
// else{go to next}

// unsigned int hashValue = 0;
// void *currentBucket = map->bucket[hashValue];
// if (isBucketEmpty(currentBucket)){check next bucket}
// else{element not here}

Map *mapNew(int length){
	Map *map = malloc(sizeof(Map));
	map->bucket = calloc(sizeof(void *),length);
	map->length = length;
	map->size = 0;
	return map;
}
void mapStore(Map *map,
							void *element,
							int (*compare)(void *, void *),
							unsigned int (*hash)(void *)){
	
	int value;
  unsigned int hashValue = 0;
  void *currentBucket = map->bucket[hashValue];
	value = hash(element);
	List *list = listNew(element , NULL);
  
	if(map->bucket[value] != NULL){
		if(compare(((List *)map->bucket[value])->data, element) == 1){Throw(ERR_SAME_ELEMENT);}
    // else{
      // while(map->bucket[value] != NULL){
        // value++;
        // }
		map->bucket[value] = listNew(element, map->bucket[value]);
    // }
	}
	else{
	map->bucket[value] = listNew(element, map->bucket[value]);
	}
}

void maplinearStore(Map *map,
							void *element,
							int (*compare)(void *, void *),
							unsigned int (*hash)(void *)){
	
	int value;
  unsigned int hashValue = 0;
  void *currentBucket = map->bucket[hashValue];
	value = hash(element);
  if(value <= map->length){
    if(map->bucket[value] != NULL){
      if(compare((map->bucket[value]), element) == 1)Throw(ERR_SAME_ELEMENT);
      else{
        while(map->bucket[value] != NULL){
        value++;
        }
        map->bucket[value] = element;
      }
    }
    else{
    map->bucket[value] = element;
    }
  // map->length--;
  }
  else{Throw(ERROR);}
}

void *mapFind(Map *map,
						 void *element,
						 int (*compare)(void *, void *),
						 unsigned int (*hash)(void *)){
	int value;
  unsigned int hashValue = 0;
  void *currentBucket = map->bucket[hashValue];
	value = hash(element);
  List *tempMap = (List *)map->bucket[value];
  
	if(map->bucket[value] != NULL){
    tempMap = tempMap->next;
    while(tempMap !=NULL){
      // if(compare(((List *)map->bucket[value])->data, ((Person *)element)->name) == 1){
      if(compare(tempMap->data, element) == 1){
        return element;
      }
      else return NULL;
      }
	}
}
void *maplinearFind(Map *map,
						 void *element,
						 int (*compare)(void *, void *),
						 unsigned int (*hash)(void *)){
	int value;
  unsigned int hashValue = 0;
  void *currentBucket = map->bucket[hashValue];
	value = hash(element);		

	if(map->bucket[value] != NULL){
    while(map->bucket[value] !=NULL){
      if(isBucketMarked(map->bucket[value])){value++;}
      else if(compare(map->bucket[value], element) == 1){
        return map->bucket[value];
      }
      else return NULL;
      }
	}
  else return NULL;
}

void *mapRemove(Map *map,
						 void *element,
						 int (*compare)(void *, void *),
						 unsigned int (*hash)(void *)){
  int value;	
  value = hash(element);
  List *tempMap = (List *)map->bucket[value];
  List *temp;
  
	if(map->bucket[value] != NULL){
      tempMap = tempMap->next;
      while(((List *)map->bucket[value])!=NULL){
      if(compare(((List *)map->bucket[value])->data, element) == 1){
        ((List *)map->bucket[value])->data = NULL;
        return ((List *)map->bucket[value])->data;
      }
      else return NULL;
      }
    }
}
void *maplinearRemove(Map *map,
						 void *element,
						 int (*compare)(void *, void *),
						 unsigned int (*hash)(void *)){
  int value;	
  value = hash(element);
  void *elem;
  
	if(map->bucket[value] != NULL){
  
    if(isBucketMarked(map->bucket[value])){value++;}
  
      while(map->bucket[value]!=NULL || value < map->length){
      // if(isBucketMarked(map->bucket[value])){
      // printf("should in remove\n");
        if(compare(map->bucket[value], element) == 1){
          if(isBucketMarked(map->bucket[value+1])){
          elem = map->bucket[value];
          map->bucket[value] = NULL;
          // printf("REMOVE\n");
          }
          else{
          elem = map->bucket[value];
          map->bucket[value] = NULL;
          // printf("REMOVED\n");
          }
          // printf("RETURN\n");
          return elem;
          }
      // }
      value++;
      // printf("ELEM\n");
      }
      return NULL;
    }
  else return NULL;
}