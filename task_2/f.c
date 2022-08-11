#include <stdio.h>
#include <math.h>
#include "matrix.h"

int f (int n, double * a, double * x, double * b)
{
	int i, j, i_0, j_0;
	double max, s, phi;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			b[i*n+j] = a[i*n+j];
		}
	}
	for (int k = 0; k < 1e6; k++)
	{
		max = 0;
		for (i = 0; i < n; i++)
		{
			for (j = i+1; j < n; j++)
			{
				s = fabs(a[i * n + j]);
				if (s > max)
				{
					max = s;
					i_0 = i; j_0 = j;
				}
			}
		}
		if (max < 1e-10)
		{
			//printf("max = %10.3e\n", max);
			for (i = 0; i < n; i++) x[i] = a[i*n+i];
			return 1;
		}
		//if (i_0 > j_0) {i = i_0; i_0 = j_0; j_0 = i;}
		//printf("i_0 = %d  j_0 = %d\n", i_0,j_0);
		//A1 = (Ut)AU
		if (fabs(a[i_0*n+i_0]-a[j_0*n+j_0]) < 1e-14) phi = M_PI/4;
		else phi = (atan(2*a[i_0*n+j_0]/(a[i_0*n+i_0]-a[j_0*n+j_0])))/2;
		//printf("phi = %lf\n", phi);
		//printf("cosphi = %lf\n", cos(phi));
		//printf("sinphi = %lf\n", sin(phi));
		for (i = 0; i < n; i++)
		{
			a[i*n+i_0] = b[i*n+i_0]*cos(phi) + b[i*n+j_0]*sin(phi);
			a[i*n+j_0] = -b[i*n+i_0]*sin(phi) + b[i*n+j_0]*cos(phi);
		}

		for (i = 0; i < n; i++)
			{b[i*n+i_0] = a[i*n+i_0];
			b[i*n+j_0] = a[i*n+j_0];}

		for (j = 0; j < n; j++)
		{
			a[i_0*n+j] = b[i_0*n+j]*cos(phi) + b[j_0*n+j]*sin(phi);
			a[j_0*n+j] = -b[i_0*n+j]*sin(phi) + b[j_0*n+j]*cos(phi);
		}

		for (j = 0; j < n; j++)
		{b[i_0*n+j] = a[i_0*n+j];
			b[j_0*n+j] = a[j_0*n+j];}
			
		//print_matrix(a,n,n);
	}
	print_matrix(a,n,n);
	for (i = 0; i < n; i++) x[i] = a[i*n+i];
	return 1;
}
