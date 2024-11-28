#include "mouse_data.h"

FILE *fptr;

void handler(int sig) {
  if (fptr != NULL) {
    fclose(fptr);
    printf("Closed file :)\n");
  }
  exit(EXIT_SUCCESS);
}