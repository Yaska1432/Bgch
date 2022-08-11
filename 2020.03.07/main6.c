#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "f.h"
static int count = 0;
double f (double x)
//{count++;return sqrt(sqrt(x));}
{count++; return x*x*x-2*x*x+x-2;}

int main (int argc, char * argv[])
{
    int num, res, m;
    double a, b, eps, x = 0;
    double * d;
    double timer;
    if (argc != 5)
    {
        printf ("Incorrect input\n");
        return 1;
    }
    sscanf (argv[1], "%d", &m);
    sscanf (argv[2], "%lf", &a);
    sscanf (argv[3], "%lf", &b);
    sscanf (argv[4], "%lf", &eps);
    d = (double *)(malloc)(3*(m+1)*sizeof(double));
    if (!d) 
    {
        printf ("Memmory allocation\n");
        return 1;
    }
    timer = clock();
    res = f6 (f, m, d, a, b, eps, &x);
    if (res == -3)
    {
        printf("Not found\n");
        free(d);
        return -1;
    }
    timer = (clock() - timer)/CLOCKS_PER_SEC;
    num = get_count(count);
    printf ("Num_of_it = %d\n", res);
    printf ("Num_fun = %d\n", num);
    printf ("Result = %e\n", x);
    printf("Resid = %e\n", f(x));
    printf("Elapsed = %.2lf\n", (double) timer);
    free(d);
    return 0;
}
