#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "f.h"
#define MAXIT 1000

int get_count (int count)
{return count;}

int f5 (double(*f)(double), double a, double b, double eps, double *x)
 {
     double fa, fb, f0, x0, x1 = 0, f1;
     int it = 1;
     fa = f(a); fb = f(b);
     if (fabs(fa-fb)<eps) return -3;
     x0 = (a+b)/2;
     f0 = f(x0);
     while (fabs(f0) > eps)
     {
         it++;
         if (it > MAXIT) return -3;
         if (fabs(fa-fb)<eps) {printf("AA\n");break;}
         if (fabs(fa-f0)<eps) return -3;
         if (fabs(f0-fb)<eps) return -3;
         if (fabs(fa) < eps)
         {x0 = a; break;}
         if (fabs(fb) < eps)
         {x0 = b; break;}
         if (fabs(f0) < eps) break;
         x1 = a*(f0*fb)/((fa-f0)*(fa-fb)) + x0*(fa*fb)/((f0-fb)*(f0-fa)) + b*(fa*f0)/((fb-fa)*(fb-f0));
         f1 = f(x1);
         if ((fabs(fa) < fabs(fb)) && (fabs(f0) < fabs(fb)) && (fabs(f1) < fabs(fb)))
         {
             fb = f1;
             b = x1;
         }
         else if ((fabs(fb) < fabs(fa)) && (fabs(f0) < fabs(fa)) && (fabs(f1) < fabs(fa)))
         {
             fa = f1;
             a = x1;
         }
         else if ((fabs(fa) < fabs(f0)) && (fabs(fb) < fabs(f0)) && (fabs(f1) < fabs(f0)))
         {
             f0 = f1;
             x0 = x1;
         }
         else return -3;
     }
     *x = x1;
     return it;
}
