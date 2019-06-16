#include <stdio.h>
#include <stdlib.h>

struct _retire_info{
  int months;
  double contribution;
  double rate_of_return;
};
typedef struct _retire_info retire_info;

double nB(double ba, retire_info ri){

  return ba*(1+ri.rate_of_return) + ri.contribution;
}

void cYM(int ms, int *y,int *m){

  *y = ms/12;
  *m = ms%12;
}

void pBI(int m, double b){

  int age, ms;
  cYM(m,&age,&ms);
  printf("Age %3d month %2d you have $%.2lf\n", age,ms,b);
}

void retirement(int startAge,double initial, retire_info working, retire_info retired){
  int m;
  int aM = startAge;
  double b = initial;

  for(m=0; m<working.months;m++){
    pBI(aM,b);
    aM++;
    b = nB(b,working);
  }
  
  for(m=0; m<retired.months;m++){
    pBI(aM,b);
    aM++;
    b = nB(b,retired);
  }
}

int main(void){
  retire_info working = {489,1000.0,0.045/12};
  retire_info retired = {384, -4000.0,0.01/12};

  int sAM = 327;
  double s = 21345;

  retirement (sAM,s,working,retired);
  return EXIT_SUCCESS;
}
