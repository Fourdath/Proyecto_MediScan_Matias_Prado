#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hasmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}


void insertMap(HashMap * map, char * key, void * value) {
  long pos = hash(key,map->capacity);
  while(map->buckets[pos] != NULL && map->buckets[pos]->key != NULL)
    {
      if(is_equal(map->buckets[pos]->key, key) == 1) return;
      pos = (pos+1) % map->capacity;
    }
  if(map->buckets[pos] == NULL)
  {
    map->buckets[pos] = createPair(key,value);
    map->size++;
  }
  else{
    map->buckets[pos]->key = key;
    map->buckets[pos]->value = value;
  }

  
  
}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)


}


HashMap * createMap(long capacity) {
  HashMap *mapa = (HashMap*)malloc(sizeof(HashMap));
  mapa->buckets = (Pair **)calloc(capacity,sizeof(Pair*));
  mapa->capacity = capacity;
  mapa->size = 0;
  mapa->current = -1;
  return mapa;
}

void eraseMap(HashMap * map,  char * key) { 
  long pos = hash(key, map->capacity);
   while(map->buckets[pos] != NULL && is_equal(map->buckets[pos]->key, key) == 0)
    {
      pos = (pos+1) % map->capacity;
    }
  if(map->buckets[pos] == NULL) return;
  map->buckets[pos]->key = NULL;
  map->size--;


}

Pair * searchMap(HashMap * map,  char * key) {   
  long pos = hash(key, map->capacity);
  while(map->buckets[pos] != NULL && is_equal(map->buckets[pos]->key, key) == 0)
    {
      pos = (pos+1) % map->capacity;
    }
  if (map->buckets[pos] == NULL || map->buckets[pos]->value == NULL) return NULL;

  map->current = pos;

  return (void *)map->buckets[pos];
}

Pair * firstMap(HashMap * map) {
  if(map == NULL || map->buckets == NULL) return NULL;

  long k;
  for(k = 0 ; k<map->capacity; k++)
    {
      if(map->buckets[k] != NULL && map->buckets[k]->key != NULL)
      {
        map->current = k;
        return map->buckets[k];
      }
    }
    return NULL;
}

Pair * nextMap(HashMap * map) {
  if(map == NULL || map->buckets == NULL) return NULL;

  long k;
  for(k = (map->current + 1) ; k<map->capacity; k++)
    {
      if(map->buckets[k] != NULL && map->buckets[k]->key != NULL)
      {
        map->current = k;
        return map->buckets[k];
      }
    }
    return NULL;
}
// Función para obtener el tamaño del HashMap
long getSize(HashMap *map) {
    return map->size;
}

// Función para obtener los valores del HashMap
void getValues(HashMap *map, void **values) {
    int i = 0;
    for (int j = 0; j < map->capacity; j++) {
        if (map->buckets[j] != NULL && map->buckets[j]->value != NULL) {
            values[i] = map->buckets[j]->value;
            i++;
        }
    }
}
