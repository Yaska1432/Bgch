#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "f.h"
# include "synchronize.h"

double norm_matrix(int n, double *a);
void func1(int n, double *a, double *b, double *x)
{
    int imax, i, j, k;
    double buf, eps = 1e-16, norm;

    norm = norm_matrix(n, a);
    for(i = 0; i < n; i++)
    {
        imax = i*n + i;
        for(j = i + 1; j < n; j++)//FIND THE MAX IN COLUMN
        {
            if(fabs(a[imax]) < fabs(a[j*n + i]))
            {
                imax = j*n + i;
            }
        }
        if(fabs(a[imax]) <= norm*eps)
        {
            printf("The column %d consists of 0\n", i);
            return;
        }
        for(j = 0; j < n; j++)//CHANGE STRINGS
        {
            buf = a[(imax/n)*n + j];
            a[(imax/n)*n + j] = a[i*n + j];
            a[i*n + j] = buf;
        }
        buf = b[i];
        b[i] = b[imax/ n];
        b[imax/n] = buf;

        for(j = i + 1; j < n; j++)//MAKING triangle
        {
            for(k = i + 1; k < n; k++)
            {
                a[j*n + k] -= a[i*n + k] * a[j*n + i] / a[i*n + i];
            }
            b[j] -= b[i] * a[j*n + i] / a[i*n + i];
        }
    }

    for(i = n - 1; i >= 0; i--)
    {
        b[i] /= a[i*n + i];
        for(j = i - 1; j >= 0; j--)
        {
            b[j] -= b[i]*a[j*n + i];
        }
        x[i] = b[i];
    }
}

double norm_matrix(int n, double *a)
{
    int i, j;
    double max, mmax;
    mmax = 0;

    for(i = 0; i < n; i++)
    {
        max = fabs(a[i]);
        for(j = 1; j < n; j++)
        {
            max += fabs(a[j*n + i]);
        }
        if(mmax < max)
        {
            mmax = max;
        }
    }
    //printf("Norma = %lf\n", mmax);
    return mmax;
}


double Scalar(double *a, double *b, int n)
{
    int i;
    double s = 0;
    for(i = 0; i < n; i++)
    {
        s += a[i] * b[i];
    }
    return s;
}

void V_M_mult(double *a, double *x0, double *x, int n)
{
    int i, j;
    double s;
    for(i = 0; i < n; i++)
    {
        s = 0;
        for(j = 0; j < n; j++)
        {
            s += a[i*n + j] * x0[j];
        }
        x[i] = s;
    }
}

void init_vectorb(double *a, double*b, int n)
{
    int i, j;
    for(i = 0; i < n; i++)
    {
        b[i] = 0;
        for(j = 0; j < (n + 1)/2; j++)
        {
            b[i] += a[i*n + 2*j];
        }
    }
}

void init_vector(double*b, int n)
{
    int i;
    for(i = 0; i < n; i++)
    {
        b[i] = 1;
    }
}
void print_matrix(double *mat, int l, int n, int m)
{
    int i, j, n_max, m_max;
    if(l > m)
    {
        m_max = m;
    }
    else
    {
        m_max = l;
    }
    if(n > m)
    {
        n_max = m;
    }
    else
    {
        n_max = n;
    }
    for(i = 0; i < m_max; i++)
    {
        for(j = 0; j < n_max; j++)
        {
            printf(" %10.3e ", mat[i*n + j]);
        }
        printf("\n");
    }
}

double f(int k, int n, int i, int j)
{
    switch (k)
    {
    case 1:
            return n - (i > j ? i : j) + 1;
    case 2:
        return (i > j ? i : j);
    case 3:
        return abs(i - j);
    case 4:
        return pow((i + j - 1), -1);
    }
    return 0;
}
void init_matrix(double *mat, int n, int k)
{
    int i, j;
    for(i = 0; i < n;i++)
        for(j = 0; j < n; j++)
            mat[i*n + j] = f(k, n, i+1, j+1);
}

int read_matrix(double *mat, int m, int n, const char* name)
{
    FILE *fp;
    int i, len;
    len = m*n;
    if(!(fp = fopen(name, "r")))
    {
        return -1;
    }
    for(i = 0; i < len; i++)
    {
        if(fscanf(fp, "%lf", mat + i) != 1)
        {
            fclose(fp);
            return -2;
        }
    }
    fclose(fp);
    return 0;
}

void n1(double *a, double *x, double *b, int n, int thread_num, int total_threads, double *norm, double *sum)
{
    int i, j;
    double scal; double *p;
    int first_row = n * thread_num;
    int last_row = n * (thread_num + 1);
    first_row /= total_threads;
    last_row = last_row / total_threads - 1;
    //print_matrix(b, n, 1, 2);
    for(i = first_row, p = a + i * n; i <= last_row; i++)
    {
        for(j = 0, scal = 0.; j < n; j++)
        {
            scal += *(p++) * x[j];
        }
        *sum += fabs(scal - b[i]);
        *norm += fabs(b[i]);
    }
    synchronize(total_threads);
}

double norm(double *a, double *x, double *b, int n)
{
    int i, j;
    double scal = 0, sum = 0, norm = 0;

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            scal += a[i*n + j] * x[j];
        }
        sum += fabs(scal - b[i]);
        scal = 0;
    }
    for(i = 0; i < n; i++)
    {
        norm += fabs(b[i]);
    }
    return sum/norm;
}

double n2(double *x, int n)
{
    int i;
    double sum = 0;
    for(i = 0; i < n; i++)
    {
        sum += fabs(x[i] - ((i + 1) % 2));
    }
    return sum;
}


