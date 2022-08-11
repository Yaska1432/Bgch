#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <pthread.h>
#include "f.h"

typedef struct _ARGS
{
    double *a, *b, *x;
    int thread_num;
    int total_threads;
    int n;
    double norma;
    double sum;
} ARGS;

//static long int threads_total_time = 0;
static pthread_mutex_t threads_total_time_mutex = PTHREAD_MUTEX_INITIALIZER;
#define N_TESTS 10
void * resid_threaded (void *pa);
void * resid_threaded (void *pa)
{
    //long int t;
    ARGS *pargs = (ARGS*)pa;
    int i;
    //t = get_time();
    for (i = 0; i < N_TESTS; i++)
    {
        n1(pargs->a, pargs->x, pargs->b, pargs->n, pargs->thread_num, pargs->total_threads, &pargs->norma, &pargs->sum);
    }
    //t = get_time() - t;
    pthread_mutex_lock (&threads_total_time_mutex);
    //threads_total_time += t;
    pthread_mutex_unlock(&threads_total_time_mutex);
    return 0;
}

int main(int argc, const char *argv[])
{
    int tmp;
    struct timespec tv1, tv2;
    pthread_t * threads;
    ARGS * args;
    int nthreads, l, m, k, ret, i, n;
    double sum, res;
    //long int t_full;
    double norma = 0, t = 0;
    double *a, *b, *x;
    const char *nameA;
    int nthread[3] = {1, 2, 4};
    for (l = 0; l < 3; l++)
    {
        norma = 0, t = 0;
        sum = 0;
        res = 0;
        nameA = 0;
        nthreads = nthread[l];
        if (!(threads = (pthread_t*) malloc (nthreads * sizeof (pthread_t))))
        {
            printf("Not enough memory\n");
            return 1;
        }
        if (!(args = (ARGS*) malloc (nthreads * sizeof(ARGS))))
        {
            printf("Not enough memory\n");
            return 1;
        }

        if (!( (argc ==  5 || argc == 4) &&(m = atoi(argv[2])) > 0 && (n = atoi(argv[1])) > 0 && sscanf(argv[3], "%d", &k) == 1))
        {
            printf("Usage: %s n m [file]\n", argv[0]);
            return 1;
        }
        if(k == 0 && argc == 5)
        {
            nameA = argv[4];
        }
        else if(k == 0 && argc != 5)
        {
            printf("k = 0 but no file in argv\n");
            return 3;
        }

        if(n <= 0 || m <= 0)
        {
            printf("Enter correct numbers!\n");
            return 3;
        }
        if(k < 0 || k > 4)
        {
            printf("Enter correct numbers!\n");
            return 3;
        }
        if(!(a = (double*) malloc(n*n*sizeof(double))))
        {
            printf("Not enough memory\n");
            return 20;
        }
        if(!(b = (double*) malloc(n*sizeof(double))))
        {
            printf("Not enough memory\n");
            free(a);
            return 21;
        }
        if(!(x = (double*) malloc(n*sizeof(double))))
        {
            printf("Not enough memory\n");
            free(a);
            free(b);
            return 22;
        }

        if(nameA)
        {
            ret = read_matrix(a, n, n, nameA);
            if(ret != 0)
            {
                switch(ret)
                {
                case -1:
                    printf("Cannot open\n");
                    break;
                case -2:
                    printf("Cannot read\n");
                    break;
                default:
                    printf("Unknown error\n");
                }
                free(a);
                free(b);
                free(x);
                return ret;
            }
        }
        else init_matrix(a, n, k);

        init_vectorb(a, b, n);

        for (i = 0; i < nthreads; i++)
        {
            args[i].a = a;
            args[i].b = b;
            args[i].x = x;
            args[i].n = n;
            args[i].thread_num = i;
            args[i].total_threads = nthreads;
            args[i].norma = norma;
            args[i].sum = sum;
        }
        func1(n,a,b,x);
        init_vectorb(a, b, n);
        
        //t_full = get_time ();
        timespec_get(&tv1, TIME_UTC);
        for (i = 0; i < nthreads; i++)
        {
            if (pthread_create(threads + i, 0, resid_threaded, args + i))
            {
                printf("cannot create thread #%d!\n", i);
                return 10;
            }
        }
        for (i = 0; i < nthreads; i++)
        {
            if (pthread_join (threads[i], 0))
                printf("cannot wait thread #%d!\n", i);
        }
        timespec_get(&tv2, TIME_UTC);
        tmp = (tv2.tv_sec - tv1.tv_sec) * 1000 + tv2.tv_nsec / 1000000 - tv1.tv_nsec / 1000000;

        //t_full = get_time () - t_full;
        res = 0;
        for (i = 0; i < nthreads; i++)
        {
            res += args[i].sum;
            t += args[i].norma;
        }
        printf("Residual = %e\n", res/t);

        printf("Time: %d.%03d, num of threads = %d\n", tmp / 1000, tmp % 1000, nthreads);

        //printf("Total time = %ld, total threads time = %ld, num of threads = %d\n\n", t_full/CLOCKS_PER_SEC, threads_total_time/CLOCKS_PER_SEC, nthreads);
        free(threads);
        free(args);
        free(a);
        free(b);
        free(x);
    }
    return 0;
}
