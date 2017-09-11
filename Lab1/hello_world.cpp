#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char **argv) {
	int nthreads, tid;

	#pragma omp parallel private(nthreads, tid) num_threads(32)
	{
		tid = omp_get_thread_num();
		printf("Hello World from thread: %d\n",tid);

		if(tid == 0) {
			nthreads = omp_get_num_threads();
			printf("Number of threads is: %d\n",nthreads);
		}
	}

	return 0;
}
