void f6 (double * a, int m, int n, int i, int j)
{
    int k;
    double t;
    for (k = 0; k < n; k++)
    {
        t = a[i*n+k];
        a[i*n+k] = a[j*n+k];
        a[j*n+k] = t;
    }
}