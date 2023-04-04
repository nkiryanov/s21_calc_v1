#include "calc_rpn.h"

int main() {
  int *ptr = malloc(sizeof(int));

  *ptr = 12;
  free(ptr);
  printf("pointer address = %p\n", ptr);
}
