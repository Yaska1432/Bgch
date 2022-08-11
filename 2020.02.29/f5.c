 #include <stdio.h>
 #include <stdlib.h>
 #include <math.h>
 //#include <time.h>
 #include "f.h"
#include "common_array.h"


 double f5 (double x, double eps)
 {
    int i, sgn = -1, f = 0, fl = 0;
    double f1, f2, y = 0;
    if (x < 0) x*=(-1);
    y = floor(x/(2*M_PI));
    x -= y*2*M_PI;
    if ((3*M_PI/2 < x) && (x < 2*M_PI))
       {x -= 2*M_PI;x *= (-1);f = 1;}
    if ((M_PI < x) && (x < 3*M_PI/2))
       {x -= M_PI; f = 1;}
    if ((M_PI/2 < x) && (x < M_PI))
       {x -= M_PI; x*=(-1);}
    if (x > 1)
       {x/=2; fl = 1;}
    f1 = x;
    f2 = sgn*f1*x*x/6;
    f1 += f2;
    for (i = 5; fabs(f2) > eps; i+=2)
    {
        sgn *= (-1);
        f2 = sgn*f2*x*x/((i-1)*i);
        f1 += f2;
    }
    if (fl)
    {
       f2 = 1 - 2*f1*f1;
       f2 = sqrt(1 - f1*f1);
    }
    if (f) return -f1;
    else return f1;
}
