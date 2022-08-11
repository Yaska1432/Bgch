#define ERROR_READ (-2)
#define ERROR_OPEN (-3)
#define SUCCESS (0)

double pow_(double n, int k);
int read_array (char * name, double * x, double * y, int n);
int read_array_new (char * name, double * x, double * y, double * d, int n);

double f1 (int n, double x0, double * x, double * y);


double f2 (int n, double x0, double * x, double * y);

double f3 (int n, double x0, double * x, double * y);

double f4 (int n, double x0, double * x, double * y, double * d); 

double f5 (double x, double eps);

double f6 (double x, double eps);

double f7 (double x, double eps);

double f8 (double x, double eps);
