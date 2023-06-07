#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <unistd.h>
#include <sys/time.h>
#include <string.h>
#ifdef _OPENMP
#include <omp.h>
#else
int omp_get_thread_num() { return 0; }
void omp_set_num_threads(int num_threads) {}
void omp_set_dynamic(int dynamic_threads) {}
double omp_get_wtime() { return 0; }
#endif

void parallel_insertion_sort(double arr[], int n)
{
    int i, j;
    double key;

#pragma omp parallel num_threads(2)
    {
        int thread_id = omp_get_thread_num();
        int start = thread_id * n / 2;
        int end = (thread_id + 1) * n / 2;

        for (i = start + 1; i < end; i++)
        {
            key = arr[i];
            j = i - 1;

            while (j >= start && arr[j] > key)
            {
                arr[j + 1] = arr[j];
                j = j - 1;
            }

            arr[j + 1] = key;
        }
    }
}

void merge_arrays(double arr[], int n, double M2_copy[])
{
    int mid = n / 2;
    double *left = arr;
    double *right = arr + mid;
    int i = 0;

    while (left < arr + mid && right < arr + n)
    {
        if (*left <= *right)
        {
            M2_copy[i] = *left;
            left++;
        }
        else
        {
            M2_copy[i] = *right;
            right++;
        }
        i++;
    }

    while (left < arr + mid)
    {
        M2_copy[i] = *left;
        left++;
        i++;
    }

    while (right < arr + n)
    {
        M2_copy[i] = *right;
        right++;
        i++;
    }

    memcpy(arr, M2_copy, n * sizeof(double));
}

int main(int argc, char *argv[])
{

    int i, j, N, M;
    double e = exp(1.0);
    double T1, T2;
    double delta_ms;
    double min = 1;
    double max = 576;
    int progress = 0;
    T1 = omp_get_wtime();
    double min_time = DBL_MAX;

    //-------------Additional-------------//
    double start_time, end_time;
    double *restrict execution_times = (double *)malloc(10 * sizeof(double));
    //-----------------------------------//

    omp_set_nested(1);
#pragma omp parallel sections num_threads(2) shared(i, progress)
    {
#ifdef _OPENMP
#pragma omp section
        {
            double time = 0;
            while (progress < 1)
            {
                double time_temp = omp_get_wtime();
                if (time_temp - time < 1)
                {
                    usleep(100);
                    continue;
                };
                printf("\rPROGRESS: %d", i);
                fflush(stdout);
                time = time_temp;
            }
        }
#endif
#pragma omp section
        {
            N = atoi(argv[1]);
            M = atoi(argv[2]);

            double *restrict M1 = (double *)malloc(N * sizeof(double));
            double *restrict M2 = (double *)malloc(N / 2 * sizeof(double));
            double *restrict M2_copy = (double *)malloc(N / 2 * sizeof(double));

            unsigned int seed;
            unsigned int *restrict seed1 = &seed;
            unsigned int *restrict seed2 = &seed;

#if defined(_OPENMP)
            omp_set_dynamic(0);
            omp_set_num_threads(M);
#endif

            for (i = 0; i < 10; i++)
            {
                //-------------Additional-------------//
                start_time = omp_get_wtime();
                //-----------------------------------//

                //------------------GENERATE---------------------//
                double min_nonzero = INFINITY;
                double sum_sin = 0.0;
                seed = i;

                for (j = 0; j < N; j++)
                {
                    M1[j] = ((double)rand_r(seed1) / (RAND_MAX)) * (max - min) + min;
                }
                for (j = 0; j < N / 2; j++)
                {
                    M2[j] = ((double)rand_r(seed2) / (RAND_MAX)) * (max * 10 - max) + max;
                }
                //---------------------------------------//

#pragma omp parallel default(none) shared(M1, M2, M2_copy, i, min, max, e, N, sum_sin, min_nonzero)
                {
                    //------------------MAP---------------------//
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
                    //------------------------------------------//

                    //------------------MERGE---------------------//
#pragma omp for
                    for (j = 0; j < N / 2; j++)
                    {
                        M2[j] = pow(M1[j], M2[j]);
                    }
                    //--------------------------------------------//

                    parallel_insertion_sort(M2, N / 2);
                    //------------------REDUCE---------------------//
#pragma omp single
                    {
                        int j;
                        for (j = 0; j < N / 2 - 1 && M2[j] == 0; j++)
                            ;
                        min_nonzero = M2[j];
                    }

#pragma omp for reduction(+ : sum_sin)
                    for (j = 0; j < N / 2; j++)
                    {
                        if ((int)(M2[j] / min_nonzero) % 2 == 0)
                        {
                            sum_sin += sin(M2[j]);
                        }
                    }
                    //--------------------------------------------//
                }
                //-------------Additional-------------//
                end_time = omp_get_wtime();
                execution_times[i] = end_time - start_time;
                //-----------------------------------//
            }
            progress = 1;

            free(M1);
            free(M2);
            free(M2_copy);
        }
    }
    //-------------Additional-------------//
    // double min_execution_time = execution_times[0];
    // for (i = 1; i < 10; i++)
    // {
    //     if (execution_times[i] < min_execution_time)
    //     {
    //         min_execution_time = execution_times[i];
    //     }
    // }
    // printf("\r%f\n", min_execution_time);
    double mid_execution_time = 0;
    for (i = 0; i < 10; i++)
    {
        mid_execution_time += execution_times[i];
    }
    mid_execution_time /= 10;

    double standard_deviation = 0;
    for (i = 0; i < 10; i++)
    {
        standard_deviation += pow(execution_times[i] - mid_execution_time, 2);
    }
    standard_deviation = sqrt(standard_deviation / 10);

    double half_interval = 2.2622 * (standard_deviation / sqrt(10));
    double lower_bound = mid_execution_time - half_interval;
    double upper_bound = mid_execution_time + half_interval;
    printf("\rlower %f\n", lower_bound);
    printf("\rupper %f\n", upper_bound);
    //-----------------------------------//

    T2 = omp_get_wtime();
    delta_ms = (T2 - T1) * 1000;
    // printf("\r%f\n", delta_ms);

    return 0;
}