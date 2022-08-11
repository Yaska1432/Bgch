#include <stdio.h>
#include <stdlib.h>
//#include <time.h>
#include <math.h>
#include "f.h"

int main(void)
{
    double x, eps, result;
    while (1)
    {
    	printf ("input x = ");
	    scanf ("%lf", &x);
	    printf ("input eps = ");
	    scanf ("%lf", &eps);
	    if (eps < 0) {printf ("incorrect input\n"); return 0;}
	    result = f6 (x, eps);
	    printf ("Result = %lf\n", result);
	    printf ("Difference = %lf\n", fabs(cos(x) - result));
	}
    return 0;
}
 
 
