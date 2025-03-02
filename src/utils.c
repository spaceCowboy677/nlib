#include <malloc.h>
#include <stdio.h>

void error(char error_text[]) {
  // Generic error handling program
  void exit();

  fprintf(stderr, "Run-time error...\n");
  fprintf(stderr, "%s\n", error_text);
  fprintf(stderr, "...now exiting to system...\n");
  exit(1);
}

float *vector(int low, int high) {
  // Allocate a vector of floats
  float *v;
  v = (float *)malloc((unsigned)(high - low + 1) * sizeof(float));
  if (!v)
    error("allocation failure in vector()");
  return v - low;
}

int *ivector(int low, int high) {
  int *v;
  v = (int *)malloc((unsigned)(high - low + 1) * sizeof(int));
  if (!v)
    error("allocation failure in ivector()");
  return v - low;
}

double *dvector(int low, int high) {
  double *v;
  v = (double *)malloc((unsigned)(high - low + 1) * sizeof(double));
  if (!v)
    error("allocation failure in dvector()");
  return v - low;
}

float **matrix(int low_row, int high_row, int low_col, int high_col) {
  int i;
  float **m;

  m = (float **)malloc((unsigned)(high_row - low_row + 1) * sizeof(float *));
  if (!m)
    error("allocation failure 1 in matrix()");
  m -= low_row;

  for (i = low_row; i < high_row; i++) {
    m[i] = (float *)malloc((unsigned)(high_col - low_col + 1) * sizeof(float));
    if (!m[i])
      error("allocation failure 2 in matrix()");
    m[i] -= low_col;
  }
  return m;
}

double **dmatrix(int low_row, int high_row, int low_col, int high_col) {
  // Allocate a matrix of doubles
  int i;
  double **m;

  m = (double **)malloc((unsigned)(high_row - low_row + 1) * sizeof(double *));
  if (!m)
    error("allocation failure 1 in matrix()");
  m -= low_row;

  for (i = low_row; i < high_row; i++) {
    m[i] =
        (double *)malloc((unsigned)(high_col - low_col + 1) * sizeof(double));
    if (!m[i])
      error("allocation failure 2 in matrix()");
    m[i] -= low_col;
  }
  return m;
}

int **imatrix(int low_row, int high_row, int low_col, int high_col) {
  // Allocate a matrix of integers
  int i;
  int **m;

  m = (int **)malloc((unsigned)(high_row - low_row + 1) * sizeof(int *));
  if (!m)
    error("allocation failure 1 in matrix()");
  m -= low_row;

  for (i = low_row; i < high_row; i++) {
    m[i] = (int *)malloc((unsigned)(high_col - low_col + 1) * sizeof(int));
    if (!m[i])
      error("allocation failure 2 in matrix()");
    m[i] -= low_col;
  }
  return m;
}

float **submatrix(float **a, int old_low_row, int old_high_row, int old_low_col,
                  int old_high_col, int new_low_row, int new_low_col) {
  int i, j;
  float **m;

  m = (float **)malloc((unsigned)(old_high_row - old_low_row + 1) *
                       sizeof(float *));
  if (!m)
    error("allocation failure in submatrix()");
  m -= new_low_row;
  for (i = old_low_row, j = new_low_row; i <= old_high_row; i++, j++)
    m[j] = a[i] + old_low_col - new_low_col;
  return m;
}

void free_vector(float *v, int low, int high) { free((char *)(v + low)); }

void free_ivector(int *v, int low, int high) { free((char *)(v + low)); }

void free_dvector(double *v, int low, int high) { free((char *)(v + low)); }

void free_matrix(float **m, int low_row, int high_row, int low_col,
                 int high_col) {
  int i;
  for (i = high_row; i >= low_row; i--)
    free((char *)(m[i] + low_col));
  free((char *)(m + low_row));
}

void free_dmatrix(double **m, int low_row, int high_row, int low_col,
                  int high_col) {
  int i;
  for (i = high_row; i >= low_row; i--)
    free((char *)(m[i] + low_col));
  free((char *)(m + low_row));
}

void free_imatrix(int **m, int low_row, int high_row, int low_col,
                  int high_col) {
  int i;
  for (i = high_row; i >= low_row; i--)
    free((char *)(m[i] + low_col));
  free((char *)(m + low_row));
}

void free_submatrix(float **b, int low_row, int high_row, int low_col,
                    int high_col) {
  free((char *)(b + low_row));
}

float **convert_matrix(float *a, int low_row, int high_row, int low_col,
                       int high_col) {
  int i, j, nrow, ncol;
  float **m;
  nrow = high_row - low_row + 1;
  ncol = high_col - low_col + 1;
  // Allocate pointers to rows
  m = (float **)malloc((unsigned)(nrow) * sizeof(float *));
  if (!m)
    error("allocation failure in convert_matrix()");
  m -= low_row;
  for (i = 0, j = low_row; i < nrow - 1; i++, j++)
    m[j] = a + ncol * i - low_col;
  return m;
}

void free_convert_matrix(float **b, int low_row, int high_row, int low_col,
                         int high_col) {
  free((char *)(b + low_row));
}
