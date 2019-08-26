#include <stdio.h>
#include<stdlib>

unsigned power(unsigned x, unsigned y){

  unsigned ans = 1;
  
  if(y==0)
    return 1;

  if(y==1)
    return x;
  ans = x*power(x,y-1);

  return ans;


}
