#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int *array, size_t n);

int main(){

  int arr[] = {};
  size_t ans = maxSeq(arr,0);
  if(ans != 0) return EXIT_FAILURE;

  int arr1[]={1,2,1,3,5,7,2,4,6,9};
  ans = maxSeq(arr1,10);
  if(ans !=4) return EXIT_FAILURE;

  int arr2[] = {1,2,3,4};
  ans = maxSeq(arr2,4);
  if(ans !=4) return EXIT_FAILURE;

  int arr3[] ={1,2,2,4};
  ans = maxSeq(arr3,4);
  if(ans!=2) return EXIT_FAILURE;

  int arr4[] = {3,-4,5,6};
  ans = maxSeq(arr4,4);
  if(ans!=3) return EXIT_FAILURE;

  int arr5[] = {10,9,7,6};
  ans = maxSeq(arr5,4);
  if(ans!= 1) return EXIT_FAILURE;
  
  int arr6[] = {0,2,5,7,8};
  ans = maxSeq(arr6, 5);
  if(ans!= 5) return EXIT_FAILURE;

  return EXIT_SUCCESS;
}
