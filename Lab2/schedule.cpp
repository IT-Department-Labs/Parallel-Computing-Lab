#include <bits/stdc++.h>
#include <omp.h>
#define N 100
#define CHUNKSIZE 10

int main(int argc, char const *argv[]) {
	/* code */
	int nthreads, tid, i, chunk;
	float a[N], b[N], c[N];

	for(i = 0; i < N; i ++) 
		a[i] = b[i] = 1.0*i;

	chunk = CHUNKSIZE;

	#pragma omp parallel shared(a, b, c, nthreads, chunk) private(i, tid) num_threads(8)
	{
		tid = omp_get_thread_num();
		if(tid == 0) {
			printf("This is the master thread\n");
		}
		printf("Thread %d starting...\n",tid);

		#pragma omp for schedule(guided, chunk)
		for(i = 0; i < N; i ++) {
			c[i] = a[i] + b[i];
			printf("Thread %d c[%d]=%f\n",tid,i,c[i]);
		}
	}

	return 0;
}