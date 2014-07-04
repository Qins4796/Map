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
	}
	else{map->bucket[value] = list;}
	
}

void *mapFind(Map *map,
						 void *element,
						 int (*compare)(void *, void *),
						 unsigned int (*hash)(void *)){
return NULL;
}