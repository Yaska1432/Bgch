void f10 (double * a, double * b, double * c, int m, int n, int k)
{
	int i, j, l;
	double s = 0;
	for (i = 0; i < m; i++)
	{
		for (l = 0; l < k; l++)
		{
			for (j = 0; j < n; j++)
			{
				if (n == k)
				{
					f3 (b, n);
					s += a[i * n + j] * b[l * k + j];
				}
				else s += a[i * n + j] * b[j * k + l];
			}
			c[i * k + l] = s;
			s = 0;
		}
	}
	if (n == k) f3 (b, n);
}

static void f3 (double * a, int n)
{
    int i, j;
    double t;
    for (i = 0; i < n; i++)
    {
        for (j = i; j < n; j++)
        {
            t = a[i*n+j];
            a[i*n+j] = a[j*n+i];
            a[j*n+i] = t;
        }
    }
}