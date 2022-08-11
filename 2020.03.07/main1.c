#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "f.h"
static int count = 0;
double f (double x)
{count++;return x*x*x-2*x*x+x-2;}

int main (int argc, char * argv[])
{
    int num, res;
    double a, b, eps, x = 0;
    double timer;
    if (argc != 4)
    {
        printf ("Incorrect input\n");
        return 1;
    }
    sscanf (argv[1], "%lf", &a);
    sscanf (argv[2], "%lf", &b);
    sscanf (argv[3], "%lf", &eps);
    timer = clock();
    res = f1 (f, a, b, eps, &x);
    timer = (clock() - timer)/CLOCKS_PER_SEC;
    num = get_count(count);
    printf ("Num_of_it = %d\n", res);
    printf ("Num_fun = %d\n", num);
    printf ("Result = %e\n", x);
    printf("Resid = %e\n", f(x));
    printf("Elapsed = %.2lf\n", (double) timer);
    return 0;
}
