#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"

kvpair_t* splitPairs(char* str){
  char* value1=strchr(str,'=');
  *value1='\0';
  value1++;
  char* n = strchr(value1,'\n');
  if(n!=NULL)*n='\0';

  kvpair_t* pair = malloc((size_t) sizeof(*pair));
  pair->key=str;
  pair->value=value1;

  return pair;
}

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  FILE *f =fopen(fname,"r");
  if(f==NULL){
    perror("Could not open file");
    return NULL;
  }

  char* line = NULL;
  size_t sz=0;
  kvpair_t* curr_pair =NULL;

  kvarray_t* kvA= malloc((size_t)(sizeof(*kvA)));
  kvA->size=0;
  kvA->arr=NULL;

  while(getline(&line,&sz,f) >=0){
    curr_pair = splitPairs(line);
    kvA->arr=realloc (kvA->arr,(kvA->size+1)*sizeof(*kvA->arr));
    kvA->arr[kvA->size] = curr_pair;
    kvA->size++;
    line = NULL;
  }
  free(line);

  if(fclose(f)!=0)
    return NULL;
  return kvA;
  
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  int i;
  for(i=0;i<pairs->size;i++){
    free(pairs->arr[i]->key);
    free(pairs->arr[i]);
  }
  free(pairs->arr);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  kvpair_t* curr_pair;
  int i;

  for(i=0;i<pairs->size;i++){
    curr_pair = pairs->arr[i];
    printf("key = '%s' value = '%s'\n",curr_pair->key, curr_pair->value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  kvpair_t* curr_pair;
  int i;

  for(i=0;i<pairs->size;i++){
    curr_pair = pairs->arr[i];
    if(!strcmp(curr_pair->key,key))
      return curr_pair->value;
  }

  return NULL;
}
