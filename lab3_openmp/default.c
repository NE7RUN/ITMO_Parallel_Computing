#include <stdio.h>
#include <omp.h>

int main()
{
    int chunk_size, schedule_type;
    enum omp_sched_t kind;

#pragma omp parallel
    {
#pragma omp single
        {
            // Get the current schedule type and chunk size
            omp_get_schedule(&kind, &chunk_size);

            switch (kind)
            {
            case omp_sched_static:
                printf("Schedule type: static\n");
                break;
            case omp_sched_dynamic:
                printf("Schedule type: dynamic\n");
                break;
            case omp_sched_guided:
                printf("Schedule type: guided\n");
                break;
            case omp_sched_auto:
                printf("Schedule type: auto\n");
                break;
            default:
                printf("Unknown schedule type\n");
            }
            printf("Chunk size: %d\n", chunk_size);
        }
    }

    return 0;
}
