#include "types/types.h"

#ifndef ODESLV_H
#define ODESLV_H

typedef double *(*sys)(double, vector);

typedef struct {
  double eps;
  double h;
} rkparams;

typedef struct {
  sys eqns;
  double x;
  vector y;
} soe;

void rkstep(soe state, rkparams params);

void rk();

#endif // !ODESLV_H
