#include "../lib/utils.h"
#include <math.h>

#define TINY 1.0e-20;

void ludcmp(float **a, int n, int *indx, float *d) {
  // Given an n x n matrix a[1..n][1..n], this routine replaces it by the LU
  // decomposition of a rowwise permutation of itself. a and n are input. a is
  // output; indx[1..n] is an output vector which records the row permutation
  // affected by the partial pivoting; d is output as +/- 1 depending on whether
  // the number of row interchanges was even or odd, respectively. This routine
  // is used in combination with lubksb to solve linear equations or invert a
  // matrix.
  int imax;
  float big, dum, sum, temp;
  float *vv;

  vv = vector(1, n);
  *d = 1.0;
  for (int i = 1; i <= n; i++) {
    big = 0.0;
    for (int j = 1; j <= n; j++) {
      if ((temp = fabs(a[i][j])) > big) {
        big = temp;
      }
    }
    if (big == 0.0) {
      error("Singular matrix in routine LUDCMP");
    }
    vv[i] = 1.0 / big;
  }
  // implement Crout's method
  for (int j = 1; j <= n; j++) {
    for (int i = 1; i < j; i++) {
      sum = a[i][j];
      for (int k = 1; k < i; k++) {
        sum -= a[i][k] * a[k][j];
      }
      a[i][j] = sum;
    }
    big = 0.0; // initialize search for largest pivot element
    for (int i = j; i < n; i++) {
      sum = a[i][j];
      for (int k = 1; k < j; k++) {
        sum -= a[i][k] * a[k][j];
      }
      a[i][j] = sum;
      if ((dum = vv[i] * fabs(sum)) >= big) {
        big = dum;
        imax = i;
      }
    }
    if (j != imax) {
      for (int k = 1; k <= n; k++) {
        dum = a[imax][k];
        a[imax][k] = a[j][k];
        a[j][k] = dum;
      }
      *d = -(*d);
      vv[imax] = vv[j];
    }
    indx[j] = imax;
    if (a[j][j] == 0.0) {
      a[j][j] = TINY;
    }
    if (j != n) {
      dum = 1.0 / (a[j][j]);
      for (int i = j + 1; i <= n; i++) {
        a[i][j] *= dum;
      }
    }
  }
  free_vector(vv, 1, n);
}

void lubksb(float **a, int n, int *indx, float b[]) {
  int ii = 0, ip;
  float sum;

  for (int i = 1; i <= n; i++) {
    ip = indx[i];
    sum = b[ip];
    b[ip] = b[i];
    if (ii) {
      for (int j = ii; j <= i - 1; j++) {
        sum -= a[i][j] * b[j];
      }
    } else if (sum) {
      ii = i;
    }
    b[i] = sum;
  }
  for (int i = n; i >= 1; i--) {
    sum = b[i];
    for (int j = i + 1; j <= n; j++) {
      sum -= a[i][j] * b[j];
    }
    b[i] = sum / (a[i][i]);
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
