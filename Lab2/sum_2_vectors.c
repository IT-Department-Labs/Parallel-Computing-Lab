#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define CHUNKSIZE 10
#define N 100

int main(int argc, char **argv) {
	int nthreads, tid, i, chunk;
	float A[N], B[N], C[N];

	for(i = 0; i < N; i ++) {
		// Initialize arrays 
		chunk = CHUNKSIZE;
		A[i] = B[i] = i*1.0;
	}

	#pragma omp parallel shared(A, B, C, nthreads, chunk) private(i, tid)  
	{
		tid = omp_get_thread_num();
		if(tid == 0) {
			nthreads = omp_get_num_threads();
			printf("Number of threads = %d\n", nthreads);
		}

		printf("Thread %d starting .... \n",tid);	

		#pragma omp for schedule(guided, chunk)
		for(i = 0; i < N; i ++) {
			C[i] = A[i] + B[i];
			printf("Thread %d:c[%d]=%f\n",tid,i,C[i]);
		}
	}

	return 0;	
}