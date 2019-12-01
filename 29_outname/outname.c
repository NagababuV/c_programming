#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "outname.h"

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  char *out = malloc((strlen(inputName)+4)*sizeof(*out));
  strcpy(out,inputName);
  out = realloc(out,(strlen(inputName)+10)*sizeof(*out));
  strcat(out,".counts");
  return out;
}
