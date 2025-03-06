#include "../lib/types/types.h"
#include "../lib/utils.h"
#include <math.h>

#define TINY 1.0e-20;

void ludcmp(tensor *a, uint *indx, double *d) {
  // Given an n x n tensor a[0..n-1][0..n-1], this routine replaces it by the LU
  // decomposition of a rowwise permutation of itself. a and n are input. a is
  // output; indx[0..n-1] is an output vector which records the row permutation
  // affected by the partial pivoting; d is output as +/- 1 depending on whether
  // the number of row interchanges was even or odd, respectively. This routine
  // is used in combination with lubksb to solve linear equations or invert a
  // matrix.
  //
  // check if matrix is square
  if (a->rows != a->cols) {
    error("Non-square matrix in routine LUDCMP");
  }

  uint imax;
  uint n = a->rows;
  double big, dum, sum, temp;
  vector vv = vecalloc(n);

  *d = 1.0;
  for (uint i = 1; i <= n; i++) {
    big = 0.0;
    for (uint j = 1; j <= n; j++) {
      if ((temp = fabs(a->data[i][j])) > big) {
        big = temp;
      }
    }
    if (big == 0.0) {
      error("Singular matrix in routine LUDCMP");
    }
    vv.data[i] = 1.0 / big;
  }
  // implement Crout's method
  for (uint j = 1; j <= n; j++) {
    for (uint i = 1; i < j; i++) {
      sum = a->data[i][j];
      for (uint k = 1; k < i; k++) {
        sum -= a->data[i][k] * a->data[k][j];
      }
      a->data[i][j] = sum;
    }
    big = 0.0; // initialize search for largest pivot element
    for (uint i = j; i < n; i++) {
      sum = a->data[i][j];
      for (uint k = 1; k < j; k++) {
        sum -= a->data[i][k] * a->data[k][j];
      }
      a->data[i][j] = sum;
      if ((dum = vv.data[i] * fabs(sum)) >= big) {
        big = dum;
        imax = i;
      }
    }
    if (j != imax) {
      for (uint k = 1; k <= n; k++) {
        dum = a->data[imax][k];
        a->data[imax][k] = a->data[j][k];
        a->data[j][k] = dum;
      }
      *d = -(*d);
      vv.data[imax] = vv.data[j];
    }
    indx[j] = imax;
    if (a->data[j][j] == 0.0) {
      a->data[j][j] = TINY;
    }
    if (j != n) {
      dum = 1.0 / (a->data[j][j]);
      for (uint i = j + 1; i <= n; i++) {
        a->data[i][j] *= dum;
      }
    }
  }
  vfree(vv);
}

void lubksb(tensor *a, uint *indx, double b[]) {
  // Solves the set of n linear equations Ax=b. A is input as the LU
  // decomposition and indx is the permutation vector determined by LUDCMP.
  // check if matrix is square
  if (a->rows != a->cols) {
    error("Non-square matrix in routine LUDCMP");
  }
  uint ii = 0, ip;
  uint n = a->rows;
  float sum;

  for (uint i = 0; i < n; i++) {
    ip = indx[i];
    sum = b[ip];
    b[ip] = b[i];
    if (ii) {
      for (uint j = ii; j <= i - 1; j++) {
        sum -= a->data[i][j] * b[j];
      }
    } else if (sum) {
      ii = i;
    }
    b[i] = sum;
  }
  for (int i = n - 1; i >= 0; i--) {
    sum = b[i];
    for (int j = i + 1; j <= n; j++) {
      sum -= a->data[i][j] * b[j];
    }
    b[i] = sum / (a->data[i][i]);
  }
}

void luslv(float **a, float **alud, int n, int indx[], float b[], float x[]) {
  // Improves a solution vector x[1..n] of the linear set of equations AX = B.
  // The matrix a[1..n][1..n] and the vectors b[1..n] and x are input, as is the
  // dimension n. Also input is alud[1..n][1..n], the LU decomposition of a as
  // returned by ludcmp, and the vector indx[1..n] also returned by that
  // routine. On output, only x is modified, to an improved set of values. It is
  // usually good enough to call this routine twice.
  double sdp;
  float *r;

  r = vector(1, n);
  for (int i = 1; i <= n; i++) {
    sdp = -b[i];
    for (int j = 1; j <= n; j++) {
      sdp += a[i][j] * x[j];
    }
    r[i] = sdp;
  }
  lubksb(alud, n, indx, r);
  for (int i = 1; i <= n; i++) {
    x[i] -= r[i];
  }
  free_vector(r, 1, n);
}

void luslv2(float **a, int n, int *indx, float *b, float d) {
  // solve a linear system of equations Ax = b, the answer of x is returned in b
  ludcmp(a, n, indx, &d);
  lubksb(a, n, indx, b);
}
