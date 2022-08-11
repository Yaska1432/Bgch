#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include <time.h>
#include "common_array.h"
#include "f.h"


double f6 (double x, double eps)
{
    int y = 0, i, sgn = -1, f = 0, fl = 0;
    double f1 = 1, f2;
    if (x < 0) x*=(-1);
    y = floor(x/(2*M_PI));
    x -= y*2*M_PI;
    if ((3*M_PI/2 < x) && (x < 2*M_PI)) {x -= 2*M_PI; x *= (-1);}
    if ((M_PI < x) && (x < 3*M_PI/2)) {x -= M_PI; f = 1;}
    if ((M_PI/2 < x) && (x < M_PI)) {x -= M_PI; x*=(-1); f = 1;}
    if (x > 1) {x/=2; fl = 1;}
    f2 = sgn*x*x/2;
    f1+=f2;
    for (i = 4; fabs(f2) > eps; i+=2)
    {
        sgn *= (-1);
        f2 = sgn*(f2*x*x)/(i*(i-1));
        f1 += f2;
    }
    if (fl) f1 = 2*f1*f1 - 1;
    if (f) return -f1;
    else return f1;
}

 /*double f6 (double x, double eps)
 {
     int y = 0, i, fact = 2, sgn = -1, f = 0, fl = 0;
     double f1 = 1, f2;
     printf("cos(x) = %lf\n", cos(x));
     if (x < 0) x*=(-1);
     y = floor(x/(2*M_PI));
     x -= y*2*M_PI;
     if ((3*M_PI/2 < x) && (x < 2*M_PI)) {x -= 2*M_PI; x *= (-1);}
     if ((M_PI < x) && (x < 3*M_PI/2)) {x -= M_PI; f = 1;}
     if ((M_PI/2 < x) && (x < M_PI)) {x -= M_PI; x*=(-1); f = 1;}
     if (x > 1) {x/=2; fl = 1;}
     f2 = sgn*pow_(x, 2)/fact;
     f1+=f2;
     for (i = 4; fabs(f2) > eps; i+=2)
     {
         fact *= (i-1)*i;
         sgn *= (-1);
         f2 = sgn*pow_(x, i)/(fact);
         f1+=f2;
     }
     if (fl) f1 = 2*f1*f1 - 1;
     if (f) return -f1;
     else return f1;
 }*/
