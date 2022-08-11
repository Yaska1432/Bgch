void f8 (double * a, int m, int n, int i, int j, int b)
{
    int k;
    for (k = 0; k < n; k++)
    {
        a[j*n+k] += a[i*n+k]*b;
    }
}