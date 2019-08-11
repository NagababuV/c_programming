#include <stdio.h>
#include <stdlib.h>


size_t maxSeq(int *array, size_t n){

  if(n <= 0)
    return 0;

  size_t len = 1;
  size_t aux = 1;
  int i = 0;

  for(i = 0; i < n-1; i++){
    if(array[i+1] > array[i])
      aux++;
    else{
      if(aux > len){
	len = aux;
	aux = 1;
      }
    }
  }

  if(len < aux)
    len = aux;

  return len;

}

