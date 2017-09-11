#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
	int nthreads, tid;
	int i = 5;

	// Fork and split into many threads
	#pragma omp parallel private(nthreads,tid) firstprivate(i) num_threads(8)
	{
		tid = omp_get_thread_num();
		printf("Hello World from %d, i=%d\n",tid,i);
		i = i+1;
		printf("Hello World from %d, i=%d\n",tid,i);

		if(tid == 0) {
			nthreads = omp_get_num_threads();
			printf("Number of threads is %d\n",nthreads);
		}
	}

	return 0;
}