#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>

void insertion_sort(double arr[], int n)
{
    int i, j;
    double key;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

int main(int argc, char *argv[])
{
    int i, j, N;
    double e = exp(1.0);
    struct timeval T1, T2;
    long delta_ms;
    double min = 1;
    double max = 576;

    N = atoi(argv[1]);

    double *restrict M1 = (double *)malloc(N * sizeof(double));
    double *restrict M2 = (double *)malloc(N / 2 * sizeof(double));
    double *restrict M2_copy = (double *)malloc(N / 2 * sizeof(double));

    unsigned int seed;
    unsigned int *restrict seed1 = &seed;
    unsigned int *restrict seed2 = &seed;

    gettimeofday(&T1, NULL);

    for (i = 0; i < 100; i++)
    {
        seed = i;

        for (j = 0; j < N; j++)
        {
            // делим каждый член на е и считаем кубический корень
            M1[j] = cbrt((((double)rand_r(seed1) / (RAND_MAX)) * (max - min) + min) / e);
        }
        for (j = 0; j < N / 2; j++)
        {

            M2[j] = ((double)rand_r(seed2) / (RAND_MAX)) * (max * 10 - max) + max;
            M2_copy[j] = M2[j];
        }
        for (j = 1; j < N / 2; j++)
        {
            M2[j] = log(fabs(tan(M2[j] + M2_copy[j - 1])));
        }
        M2[0] = log(fabs(tan(M2[0])));

        for (j = 0; j < N / 2; j++)
        {
            M2[j] = pow(M1[j], M2[j]);
        }
        insertion_sort(M2, N / 2);
        double min_nonzero = INFINITY;
        double sum_sin = 0.0;
        for (j = 0; j < N / 2; j++)
        {
            if (M2[j] > 0 && M2[j] < min_nonzero)
            {
                min_nonzero = M2[j];
            }
            if ((int)(M2[j] / min_nonzero) % 2 == 0)
            {
                sum_sin += sin(M2[j]);
            }
        }
        printf("%lf\n", sum_sin);
    }
    // printf("%lf\n", sum_sin);
    gettimeofday(&T2, NULL);
    delta_ms = 1000 * (T2.tv_sec - T1.tv_sec) + (T2.tv_usec - T1.tv_usec) / 1000;
    printf("\nN=%d. Milliseconds passed: %ld\n", N, delta_ms);

    free(M1);
    free(M2);
    free(M2_copy);

    return 0;
}
