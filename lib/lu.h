
void ludcmp(float **a, int n, int *indx, float *d);

void lubksb(float **a, int n, int *indx, float b[]);

void luslv(float **a, float **alud, int n, int indx[], float b[], float x[]);

void luslv2(float **a, int n, int *indx, float *b, float d);
