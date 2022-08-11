#include <stdio.h>
#include <math.h>
#include <time.h>

int search (double EPS,double a, double *x, double *y, int max_it);
double n (double x1, double y1, double x2, double y2);
double f (double x, double y, double a);
double g (double x, double y);

int main(int argc, char **argv)
{
    int r;
    double a;
    double EPS;
    double x, y;
    double time;
    if(argc != 3)
    {
        printf("usage %s (insert double a = 0.8) (double eps)\n", argv[0]);
        return 1;
    }
    if(sscanf(argv[1], "%lf", &a) != 1 || sscanf(argv[2], "%lf", &EPS) != 1)
    {
        printf("can not read\n");
        return 2;
    }
    if (EPS <= 0) printf("number eps must be positive\n");
    time = clock();
    r = search(EPS, a, &x, &y, (int)(log(EPS)/log(0.75)));
    if(r < 0) printf("error\n");
    else printf("result: %lf, %lf\nnevyazka = %le\nit = %d\nElapsed = %.2lf\n", x, y, n(x, y, f(x, y, a), g(x, y)), r, time/CLOCKS_PER_SEC);
    return 0;
}

double f (double x, double y, double a)
{
return ((exp(-(x/(sqrt(1+x*x))+sin(y))*(x/(sqrt(1+x*x))+sin(y))))/(1+a));
}

double g (double x, double y)
{
return (((2*log(log(sqrt(1+x*x))))-sin(y)+1)/2);
}

double n (double x1, double y1, double x2, double y2)
{
return sqrt( (x1-x2) * (x1-x2) + (y1 - y2) * (y1 - y2) );
}

int search (double EPS, double a, double *x, double *y, int max_it)
{
    double x0 = 1/(1+a), y0 = 100, x1, y1;
    int i;
    x1 = f(x0, y0, a);
    y1 = g(x0, y0);
    //for(i = 0; i < max_it; i ++)
    while(n(x0, y0, x1, y1) > EPS)
    {
        if(n(x0, y0, x1, y1) < EPS)
        {
            *x = x1;
            *y = y1;
            return i;
        }
        x0 = x1;
        y0 = y1;
        x1 = f(x0, y0, a);
        y1 = g(x0, y0);
    }
    *x=x1;
    *y=y1;
    return max_it;
}
