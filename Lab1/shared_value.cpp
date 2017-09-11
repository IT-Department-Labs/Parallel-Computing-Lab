#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char const *argv[]) {
	int nthreads, tid, value = 0;

	#pragma omp parallel private(nthreads, tid) shared(value)
	{
		tid = omp_get_thread_num();
		printf("Hello World from thread %d\n",tid);

		value += tid;

		if(tid == 0) {
			nthreads = omp_get_num_threads();
			printf("Number of threads is: %d\n",nthreads);
		}
	}

	printf("%d\n",value);

	return 0;
}