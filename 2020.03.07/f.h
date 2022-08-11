double f (double x);
double d (double x);
int get_count (int count);
void rewrite(double *a, double*b, int n);
int Newt (double * ar1, double * ar2, int n, double *p);

int f1 (double (*f)(double), double a, double b, double eps, double *x);
int f2 (double(*f)(double), double(*d)(double), double x0, double eps, double *x);
int f3 (double(*f)(double), double a, double b, double eps, double *x);
int f4 (double(*f)(double), double a, double b, double eps, double *x);
int f5 (double(*f)(double), double a, double b, double eps, double *x);
int f6 (double(*f)(double), int m, double * d, double a, double b, double eps, double *x);
int f7 (double(*f)(double), double x0, double eps, double *x);
int f8 (double(*f)(double), double a, double b, double eps, double *x);
int f9 (double(*f)(double), double a, double b, double eps, double *x);
