#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "f.h"
static int count = 0;
double f (double x)
{count++; return x*x/10;}

int main (int argc, char * argv[])
{
    int num, res;
    double eps, x0, 
    x = 0;
    double timer;
    if (argc != 3)
    {
        printf ("Incorrect input\n");
        return 1;
    }
    sscanf (argv[1], "%lf", &x0);
    sscanf (argv[2], "%lf", &eps);
    timer = clock();
    res = f7 (f, x0, eps, &x);
    num = get_count(count);
    timer = (clock() - timer)/CLOCKS_PER_SEC;
    if (res == -3)
    {
        printf ("Not found\n");
        return -1;
    }
    printf ("Num_of_it = %d\n", res);
    printf ("Num_fun = %d\n", num);
    printf ("Result = %e\n", x);
    printf("Resid = %e\n", f(x));
    printf("Elapsed = %.2lf\n", (double) timer);
    return 0;
}
