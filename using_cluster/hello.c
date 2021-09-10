#include <stdio.h>
#include <omp.h>


void main()
{
#pragma omp parallel
        {
                int tid = omp_get_thread_num();
                printf("Hello from %d\n", tid);
        }
}
