void init_vectorb(double *a, double*b, int n);
void print_matrix(double *mat, int l, int n, int m);
double f(int k, int n, int i, int j);
void init_matrix(double *mat, int n, int k);
int read_matrix(double *mat, int m, int n, const char* name);
void init_vector(double*b, int n);
void V_M_mult(double *a, double *x0, double *x, int n);
double Scalar(double *a, double *b, int n);
void n1(double *a, double *x, double *b, int n, int thread_num, int total_threads, double *norm, double *sum);
double n2(double *x, int n);
double norm_matrix(int n, double *a);
void func1(int n, double *a, double *b, double *x);
double norm(double *a, double *x, double *b, int n);

