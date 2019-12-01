#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"
#include "counts.h"
#include "outname.h"

counts_t * countFrFile(FILE* f, kvarray_t * kvPairs){
  char *line=NULL;
  size_t size=0;
  char *key = NULL;
  char *value = NULL;

  counts_t *ans = createCounts();
  if(ans==NULL)
    return NULL;

  while(getline(&line,&size,f)>=0){
    int len = strlen(line);
    if(line[len-1] == '\n'){
      key = realloc(key,len*sizeof(*key));
      strncpy(key,line,len);
      key[len-1] = '\0';
    }else{
      key = realloc(key,(len+1)*sizeof(*key));
      strncpy(key,line,len);
      key[len] = '\0';
    }
    value = lookupValue(kvPairs,key);
    addCount(ans,value);
  }
  free(line);
  free(key);

  return ans;

}

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  FILE * f=fopen(filename,"r");
  if(f==NULL)
    return NULL;

  counts_t * ans= countFrFile(f,kvPairs);
  if(ans ==NULL)
    return NULL;

  fclose(f);
  return ans;
  
  /*
  counts_t *ans = createCounts();
  FILE* f=fopen(filename,"r");
  if(f==NULL)
    return NULL;

  char* line = NULL;
  size_t sz=0;

  while(getline(&line,&sz,f)>=0){
    char* n= strchr(line,'\n');
    if(n!=NULL)
      *n = '\0';
    char* x = lookupValue(kvPairs,line);
    addCount(ans,x);
  }
  free(line);
  if(fclose(f)!=0)
    return NULL;
  
    return ans;*/
  
  
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  if(argc<3){
    fprintf(stderr,"no enough arguments");
    return EXIT_FAILURE;
  }
 //read the key/value pairs from the file named by argv[1] (call the result kv)
  kvarray_t *kv=readKVs(argv[1]);
  if(kv == NULL){
    fprintf(stderr,"Error reading pairs");
    return EXIT_FAILURE;
  }
 //count from 2 to argc (call the number you count i)
  int i;
  for (i=2;i<argc;i++){
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    counts_t *c=countFile(argv[i],kv);
    if(c==NULL)
      return EXIT_FAILURE;
    //compute the output file name from argv[i] (call this outName)
    char* outName = computeOutputFileName(argv[i]);
    //open the file named by outName (call that f)
    FILE *f = fopen(outName,"w");
    if(f==NULL){
      fprintf(stderr,"Error in outFile");
      return EXIT_FAILURE;
    }
    //print the counts from c into the FILE f
    printCounts(c,f);
    //close f
    if(fclose(f)!=0)
      return EXIT_FAILURE;
    //free the memory for outName and c
    free(outName);
    freeCounts(c);
  }


 //free the memory for kv
  freeKVs(kv);
  return EXIT_SUCCESS;
}
