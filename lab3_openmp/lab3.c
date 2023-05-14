#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <omp.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int i, j, N, M, CHUNKSIZE;
    const char *SCHEDULE;
    double e = exp(1.0);
    struct timeval T1, T2;
    long delta_ms, extra2;
    double min = 1;
    double max = 576;

    N = atoi(argv[1]);
    // M = atoi(argv[2]);
    // SCHEDULE = argv[3];
    /*
        enum omp_sched_t schedule_type;
        if (strcmp(SCHEDULE, "static") == 0)
        {
            schedule_type = omp_sched_static;
        }
        else if (strcmp(SCHEDULE, "dynamic") == 0)
        {
            schedule_type = omp_sched_dynamic;
        }
        else if (strcmp(SCHEDULE, "guided") == 0)
        {
            schedule_type = omp_sched_guided;
        }
        else if (strcmp(SCHEDULE, "auto") == 0)
        {
            schedule_type = omp_sched_auto;
        }
        CHUNKSIZE = atoi(argv[4]);
    */

#if defined(_OPENMP)
    omp_set_dynamic(0);
    omp_set_num_threads(M);
    omp_set_schedule(schedule_type, CHUNKSIZE);
#endif

    double *restrict M1 = (double *)malloc(N * sizeof(double));
    double *restrict M2 = (double *)malloc(N / 2 * sizeof(double));
    double *restrict M2_copy = (double *)malloc(N / 2 * sizeof(double));

    unsigned int seed;
    unsigned int *restrict seed1 = &seed;
    unsigned int *restrict seed2 = &seed;

    gettimeofday(&T1, NULL);

    for (i = 0; i < 100; i++)
    {
        double min_nonzero = INFINITY;
        double sum_sin = 0.0;
        seed = i;

        for (j = 0; j < N; j++)
        {
            // делим каждый член на е и считаем кубический корень
            M1[j] = ((double)rand_r(seed1) / (RAND_MAX)) * (max - min) + min;
        }
        for (j = 0; j < N / 2; j++)
        {
            M2[j] = ((double)rand_r(seed2) / (RAND_MAX)) * (max * 10 - max) + max;
        }

#pragma omp parallel default(none) shared(M1, M2, M2_copy, i, min, max, e, N, sum_sin, min_nonzero)
        {
#pragma omp for
            for (j = 0; j < N; j++)
            {
                M1[j] = cbrt(M1[j] / e);
            }

#pragma omp for
            for (j = 0; j < N / 2; j++)
            {
                M2_copy[j] = M2[j];
            }

#pragma omp for
            for (j = 1; j < N / 2; j++)
            {
                if (j == 0)
                {
                    M2[0] = log(fabs(tan(M2[0])));
                }
                else
                {
                    M2[j] = log(fabs(tan(M2[j] + M2_copy[j - 1])));
                }
            }

#pragma omp for
            for (j = 0; j < N / 2; j++)
            {
                M2[j] = pow(M1[j], M2[j]);
            }

#pragma omp for reduction(+ : sum_sin)
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
        }
    }
    gettimeofday(&T2, NULL);
    delta_ms = 1000 * (T2.tv_sec - T1.tv_sec) + (T2.tv_usec - T1.tv_usec) / 1000;
    printf("%ld\n", delta_ms);
    free(M1);
    free(M2);
    free(M2_copy);

    return 0;
}
