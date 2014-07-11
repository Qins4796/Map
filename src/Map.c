#include "Map.h"
#include "List.h"
#include "Person.h"
#include <stdio.h>
#include <malloc.h>
#include "ErrorCode.h"
#include "CException.h"

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
	value = hash(element);
	List *list = listNew(element , NULL);
	if(map->bucket[value] != NULL){
		if(compare(((List *)map->bucket[value])->data, element) == 1)Throw(ERR_SAME_ELEMENT);
		map->bucket[value] = listNew(element, map->bucket[value]);
	}
	else{
	map->bucket[value] = listNew(element, map->bucket[value]);
	}
	
}

void *mapFind(Map *map,
						 void *element,
						 int (*compare)(void *, void *),
						 unsigned int (*hash)(void *)){
	int value;
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