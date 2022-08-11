int f2 (double * a, int n)
{
    int i, s = 0;
    for (i = 0; i < n; i++)
    {
        s+=a[i*n+i];
    }
    return s;
}