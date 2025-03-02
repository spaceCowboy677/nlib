
void error(char error_text[]);

float *vector(int low, int high);

int *ivector(int low, int high);

double *dvector(int low, int high);

float **matrix(int low_row, int high_row, int low_col, int high_col);

double **dmatrix(int low_row, int high_row, int low_col, int high_col);

int **imatrix(int low_row, int high_row, int low_col, int high_col);

float **submatrix(float **a, int old_low_row, int old_high_row, int old_low_col,
                  int old_high_col, int new_low_row, int new_high_col);

void free_vector(float *v, int low, int high);

void free_ivector(int *v, int low, int high);

void free_dvector(double *v, int low, int high);

void free_matrix(float **m, int low_row, int high_row, int low_col,
                 int high_col);

void free_dmatrix(double **m, int low_row, int high_row, int low_col,
                  int high_col);

void free_imatrix(int **m, int low_row, int high_row, int low_col,
                  int high_col);

void free_submatrix(float **b, int low_row, int high_row, int low_col,
                    int high_col);

float **convert_matrix(float *a, int low_row, int high_row, int low_col,
                       int high_col);

void free_convert_matrix(float **b, int low_row, int high_row, int low_col,
                         int high_col);

void linspace(void *begin, void *end, int spacing);
