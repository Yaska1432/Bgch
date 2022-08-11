#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include <time.h>
#include "f.h"
#include "common_array.h"
int main(void)
{
    double x, eps = 1, result;
    while (1)
    {
        printf ("input x = ");
        scanf ("%lf", &x);
        printf ("input eps = ");
        scanf ("%lf", &eps);
        if (eps < 0) {printf ("incorrect input\n"); return 0;}
        result = f7 (x, eps);
        printf ("Result = %lf\n", result);
        printf ("Difference = %e\n", fabs(pow(M_E, x) - result));
    }
    return 1;
}
