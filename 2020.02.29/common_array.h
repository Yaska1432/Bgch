#include "f.h"

double pow_(double n, int k)
{
    double res = 1;

    if (k < 0) {k*=(-1); n = (1/n);}
    while(k)
    {
        if (k & 1) res *= n;
        n *= n;
        k >>= 1;
    }
    return res;
}

int read_array (char * name, double * x, double * y, int n)
{
    FILE *fp;
    int i;
    if (!(fp = fopen(name, "r"))) return ERROR_OPEN;
    for (i = 0; i < n; i++)
    {
        if (fscanf (fp, "%lf", x + i) != 1)
        {
            fclose (fp);
            return ERROR_READ;
        }
        if (fscanf (fp, "%lf", y + i) != 1)
        {
            fclose (fp);
            return ERROR_READ;
        }
    }
    fclose (fp);
    return 0;
} 

int read_array_new (char * name, double * x, double * y, double * d, int n)
{
    FILE *fp;
    int i;
    if (!(fp = fopen(name, "r"))) return ERROR_OPEN;
    for (i = 0; i < n; i++)
    {
        if (fscanf (fp, "%lf", x + i) != 1)
        {
            fclose (fp);
            return ERROR_READ;
        }
        if (fscanf (fp, "%lf", y + i) != 1)
        {
            fclose (fp);
            return ERROR_READ;
        }
        if (fscanf (fp, "%lf", d + i) != 1)
        {
            fclose (fp);
            return ERROR_READ;
        }
    }
    fclose (fp);
    return 0;
} 
