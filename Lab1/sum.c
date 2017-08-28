#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(void){

	int sum = 0;
	int nthreads, tid;

	#pragma omp parallel private(nthreads, tid) shared(sum)	
	{	
		tid = omp_get_thread_num();
		sum += tid+1;
		printf("Sum of numbers till thread %d  is %d\n",tid,sum);

		if(tid == 0) {
			nthreads = omp_get_num_threads();
		}
	}
	printf("Sum is %d\n",sum);

	return 0;
}
