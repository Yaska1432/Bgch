#include <stdio.h>
#include <stdlib.h>
//#include <time.h>
#include <math.h>
#include "f.h"

int main(void)
{
    double x, eps, result;
    while(1)
    {
        printf ("input x = ");
        scanf ("%lf", &x);
        printf ("input eps = ");
        scanf ("%lf", &eps);
        if (eps < 0) return 1;
        result = f5 (x, eps);
        printf ("Result = %lf\n", result);
        printf ("Difference = %e\n", fabs(sin(x) - result));
    }
    return 0;
}
 
 
