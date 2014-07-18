#ifndef Map_H
#define Map_H

#define isBucketEmpty(x) ((x) == NULL || (x) == (void *) -1 )   //for Store
#define isBucketMarked(x) ((x) == (void *) -1 )                 //for Find & Remove

typedef struct Map Map;

struct Map{
	void **bucket;
	int length;     // Total number of bucket
	int size;       // Number of bucket used
};

Map *mapNew(int length);

//Implementing Seperate Chaining Method
void mapStore(Map *map,
							void *element,
							int (*compare)(void *, void *),
							unsigned int (*hash)(void *));
//Implementing Linear Probing Method
void maplinearStore(Map *map,
							void *element,
							int (*compare)(void *, void *),
							unsigned int (*hash)(void *));
void *mapFind(Map *map,
						 void *element,
						 int (*compare)(void *, void *),
						 unsigned int (*hash)(void *));
void *maplinearFind(Map *map,
						 void *element,
						 int (*compare)(void *, void *),
						 unsigned int (*hash)(void *));             
void *mapRemove(Map *map,
						 void *element,
						 int (*compare)(void *, void *),
						 unsigned int (*hash)(void *));
void *maplinearRemove(Map *map,
						 void *element,
						 int (*compare)(void *, void *),
						 unsigned int (*hash)(void *));
#endif // Map_H
