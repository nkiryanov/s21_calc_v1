#include <stdio.h>
#include <stdlib.h>

#include "calc_token.h"
#include "match_token.h"

int main() {
  typedef double (*operator)(double, double);

  calc_token_t token = {
      .token_type = 50,
      .storage.number = 23,
  };

  
  match_token("mod", &token);

  operator oper = token.storage.operator.operator;

  double y = (*oper)(5, 4);

  printf("return = %lf\n", y);
}
