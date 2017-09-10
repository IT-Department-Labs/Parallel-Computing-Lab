#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
	int n, i;
	scanf("%d",&n);
	int A[n];

	for(int i = 0; i < n; i ++) {
		A[i] = i;
	}

	int key = n/2-1;

	#pragma omp parallel private(i)
	{
		printf("Total number of threads: %d\n",omp_get_num_threads());

		#pragma omp for schedule(static)
		for(int i = 0; i < n; i ++) {
			if(A[i] == key) {
				printf("Key %d found at position %d: Thread %d\n",key,i,omp_get_thread_num());
			}
		}
	}

	return 0;
}