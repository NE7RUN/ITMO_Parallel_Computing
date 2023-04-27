#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include "FW_1.3.1_Lin64/fwBase.h"
#include "FW_1.3.1_Lin64/fwSignal.h"

/*
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
*/

int main(int argc, char *argv[])
{
    int i, j, N, M;
    double e = exp(1.0);
    struct timeval T1, T2;
    long delta_ms;
    double min = 1;
    double max = 576; // Based on personal data

    N = atoi(argv[1]);  // Размерность массива
    M = atoi(argv[2]);  // кол-во потоков
    fwSetNumThreads(M); // для установки количества создаваемых параллельной библиотекой потоков, задействуемых при выполнении распараллеленных Framewave-функций

    Fw64f *restrict M1 = (Fw64f *)malloc(N * sizeof(Fw64f));
    Fw64f *restrict M2 = (Fw64f *)malloc(N / 2 * sizeof(Fw64f));
    Fw64f *restrict M2_copy = (Fw64f *)malloc(N / 2 * sizeof(Fw64f));

    unsigned int seed;
    unsigned int *restrict seed1 = &seed;
    unsigned int *restrict seed2 = &seed;

    gettimeofday(&T1, NULL);

    for (i = 0; i < 100; i++)
    {
        seed = i;
        // Generate // Map // Тут при формировании массива было деление на е и вычисление кубического корня
        for (j = 0; j < N; j++)
        {
            M1[j] = (((double)rand_r(seed1) / (RAND_MAX)) * (max - min) + min) / e;
        }
        for (j = 0; j < N / 2; j++)
        {
            M2[j] = ((double)rand_r(seed2) / (RAND_MAX)) * (max * 10 - max) + max;
            // M2_copy[j] = M2[j];
        }
        fwsCopy_64f(M2, M2_copy, N / 2); // Создаем копию массива М2
        fwsCbrt_64f_A53(M1, M1, N);      // Кубический корень (деление на е при формировании)

        /*
        for (j = 1; j < N / 2; j++)
        {
            M2[j] = log(fabs(tan(M2[j] + M2_copy[j - 1])));
        }
        M2[0] = log(fabs(tan(M2[0])));
        */
        for (j = 1; j < N / 2; j++)
        {
            M2[j] = M2[j] + M2_copy[j - 1];
        }
        // натуральный логарифм модуля тангенса
        fwsTan_64f_A53(M2, M2, N / 2);
        fwsAbs_64f_I(M2, N / 2);
        fwsLn_64f_I(M2, N / 2);

        // Merge
        /*
        for (j = 0; j < N / 2; j++)
        {
            M2[j] = pow(M1[j], M2[j]);
        }
        */
        // возводим в степень
        fwsPow_64f_A53(M1, M2, M2, N / 2);

        // Sort
        // insertion_sort(M2, N / 2);
        // Reduce
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
        // printf("%lf\n", sum_sin);
    }
    // printf("%lf\n", sum_sin);
    gettimeofday(&T2, NULL);
    delta_ms = 1000 * (T2.tv_sec - T1.tv_sec) + (T2.tv_usec - T1.tv_usec) / 1000;
    // printf("\nN=%d. Milliseconds passed: %ld\n", N, delta_ms);
    printf("%ld\n", delta_ms);

    free(M1);
    free(M2);
    free(M2_copy);

    return 0;
}
