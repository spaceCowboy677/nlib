#include "../lib/types/types.h"

uint uneqllen(uint len1, uint len2) {
  if (len1 != len2) {
    return 1;
  }
  return 0;
}

// methods associated with vector
vector vecalloc(uint N) {
  vector v;
  v.size = N;
  v.data = (double *)malloc((unsigned)N * sizeof(*v.data));
  if (!v.data) {
    error("allocation failure in vecalloc()");
  }
  return v;
}

void vfree(vector vec) { free((char *)(vec.data)); }

void vadd(const vector *v1, const vector *v2, vector *result) {
  if (uneqllen(v1->size, v2->size)) {
    // we'll need to check for result as well but I'm lazy atm
    error("V1 length must equal V2 lenght in dot");
  }
  for (uint i = 0; i < v1->size; i++) {
    result->data[i] = v1->data[i] + v2->data[i];
  }
}

void vsub(const vector *v1, const vector *v2, vector *result) {
  if (uneqllen(v1->size, v2->size)) {
    // we'll need to check for result as well but I'm lazy atm
    error("V1 length must equal V2 lenght in dot");
  }
  for (uint i = 0; i < v1->size; i++) {
    result->data[i] = v1->data[i] - v2->data[i];
  }
}

double dot(const vector *v1, const vector *v2) {
  if (uneqllen(v1->size, v2->size)) {
    error("V1 length must equal V2 length in dot");
  }
  double prod = 0.0;
  for (uint i = 0; i < v1->size; i++) {
    prod += v1->data[i] * v2->data[i];
  }
  return prod;
}

void cross(const vector *v1, const vector *v2, vector *result) {
  if (uneqllen(v1->size, v2->size)) {
    error("V1 length must equal V2 length in dot");
  }
}

// methods associated with tensor struct
tensor talloc(uint N, uint M) {
  tensor m;
  m.rows = N;
  m.cols = M;
  // allocate "rows"
  m.data = (double **)malloc((unsigned)(N) * sizeof(double *));
  if (!m.data) {
    error("allocation failure in tensor rows");
  }
  // allocate "columns"
  for (uint i = 0; i < N; i++) {
    m.data[i] = (double *)malloc((unsigned)M * sizeof(double));
    if (!m.data[i]) {
      error("allocation failure in tensor columns");
    }
  }
  return m;
}

void tfree(tensor A) {
  // free each columns
  for (uint i = 0; i < A.rows; i++) {
    free((char *)A.data[i]);
  }
  // free rows
  free((char *)A.data);
}

void tadd(const tensor *t1, const tensor *v2, tensor *result) {}

void tsub(const tensor *v1, const tensor *v2, tensor *result) {}

void matmul(const tensor *t1, const tensor *t2, tensor *result) {}

void mul(const tensor *A, const vector *b, const vector *result) {}

double det(const tensor *A) {}

double inv(const tensor *A) {}
