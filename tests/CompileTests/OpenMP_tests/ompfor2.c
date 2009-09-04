/*
 loop scheduling
*/
#include <stdio.h>
#ifdef _OPENMP
#include <omp.h>
#endif 
int a[20];

int foo(int lower, int upper, int stride)
{
  int i;
printf("---------default schedule--------------\n");  
#pragma omp for  nowait
  for (i=lower;i<upper;i+=stride)
  {
    a[i]=i*2;
    printf("Iteration %2d is carried out by thread %2d\n",\
        i, omp_get_thread_num());
  }

#pragma omp barrier
printf("---------static schedule--------------\n");  
#pragma omp for schedule(static)
  for (i=lower;i<upper;i+=stride)
  {
    a[i]=i*2;
    printf("Iteration %2d is carried out by thread %2d\n",\
        i, omp_get_thread_num());
  }

printf("---------(static,5) schedule--------------\n");  
#pragma omp for schedule(static,5)
  for (i=lower;i<upper;i+=stride)
  {
    a[i]=i*2;
    printf("Iteration %2d is carried out by thread %2d\n",\
        i, omp_get_thread_num());
  }


printf("---------(dynamic,3) schedule--------------\n");  
#pragma omp for schedule(dynamic,3) ordered
  for (i=lower;i<upper;i+=stride)
  {
    a[i]=i*2;
    printf("Iteration %2d is carried out by thread %2d\n",\
        i, omp_get_thread_num());
  }

printf("---------(guided) schedule--------------\n");  
#pragma omp for schedule(guided) nowait
  for (i=lower;i<upper;i+=stride)
  {
    a[i]=i*2;
    printf("Iteration %2d is carried out by thread %2d\n",\
        i, omp_get_thread_num());
  }

printf("---------(runtime) schedule--------------\n");  
#pragma omp for schedule(runtime)
  for (i=lower;i<upper;i+=stride)
  {
    a[i]=i*2;
    printf("Iteration %2d is carried out by thread %2d\n",\
        i, omp_get_thread_num());
  }

}

int main(void)
{
  //#pragma omp parallel for schedule (auto)
#pragma omp parallel
  {
#pragma omp single
    printf ("Using %d threads.\n",omp_get_num_threads());
   foo(0,20,3);
  }
}

