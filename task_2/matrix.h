enum RETURN_CODES
{SUCCESS, ERROR_READ, ERROR_OPEN};

int read_matrix (double * a, int m, int n, const char * name);
void init_matrix (double * a, int m, int n, int k);
void print_matrix (double * a, int m, int n);
void init_E (double * a, int n);
void init_vector (double * a, int n);
double fun (int n, int i, int j, int k);
int matrix (double * a, int n, int k, const char * name);

void print_vector (double * x, int n);

double norm (double * a, double * x, int n);
double num (double * a, double * b, int n);
void fun1 (double * a, double * w, double * r, int n);
void fun2 (double * a, double * w, double * r, int n);

int f (int n, double * a, double * x, double * b);
