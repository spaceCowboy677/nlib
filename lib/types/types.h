#include "../utils.h"
#include <stdlib.h>

#ifndef TYPES_H
#define TYPES_H

// vector structure
typedef struct {
  uint size;
  double *data;
} vector;

// methods associated with vector
vector vecalloc(uint N);

void vfree(vector vec);

void vadd(const vector *v1, const vector *v2, vector *result);

void vsub(const vector *v1, const vector *v2, vector *result);

double dot(const vector *v1, const vector *v2);

void cross(const vector *v1, const vector *v2, vector *result);

// tensor structure
typedef struct {
  uint rows;
  uint cols;
  double **data;
} tensor;

// methods associated with tensor struct
tensor talloc(uint N, uint M); // allocates an N x M tensor

void tfree(tensor A);

void tadd(const tensor *t1, const tensor *v2, tensor *result);

void tsub(const tensor *v1, const tensor *v2, tensor *result);

void matmul(const tensor *t1, const tensor *t2, tensor *result);

void mul(const tensor *A, const vector *b, const vector *result);

double det(const tensor *A);

double inv(const tensor *A);

#endif // !TYPES_H
