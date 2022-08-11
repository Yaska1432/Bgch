#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include <time.h>
#include "f.h"

int main(void)
{
    double x, eps, result;
    while(1)
    {
        printf ("input x = ");
        scanf ("%lf", &x);
        if (x < 0) {printf ("incorrect input\n"); return 0;}
        printf ("input eps = ");
        scanf ("%lf", &eps);
        if (eps < 0) {printf ("incorrect input\n"); return 0;}
        result = f8 (x, eps);
        printf ("Result = %lf\n", result);
        printf ("Difference = %e\n", fabs(log(x) - result));
    }
    return 0;
}
