#include <stdio.h>
#include <sys/time.h>
#ifdef _OPENMP
#include <omp.h>
#else
#define omp_get_thread_num() 0
#define omp_get_num_threads() 1
#define omp_set_num_threads(T) 0
#endif

void gettime(double *t) {
	struct timeval tv;
	gettimeofday(&tv, (void *)0);
	*t = tv.tv_sec + 1.0e-6*tv.tv_usec;
}

long fib_number (int n) {

	long fn, fn1, fn2;

	if ( n == 0 || n == 1) return(n);

	if ( n < 20 ) 
		return (fib_number(n-1) + fib_number(n-2));


	#pragma omp task shared(fn1)
	{ 
		fn1 = fib_number(n-1); 
	}

	#pragma omp task shared(fn2)
	{ 
		fn2 = fib_number(n-2); 
	}

	#pragma omp taskwait
	fn = fn1 + fn2;

	return(fn);

}

int main (int argc, char* argv[]) {
	
	long result;
	int N = 0;
	int i;
	double initial, final, temp;
	int num_threads;
	
	if (argv[1] != NULL)
		N = atoi(argv[1]);
	
	gettime(&initial);

	#pragma omp parallel
	{
		#pragma omp single nowait
		{
			num_threads =  omp_get_num_threads();
			for (i=1; i<N; i++) {
				result = fib_number(i);
				printf("%lu, ",result);
			}
		}	
	}	

	printf("...\n");
	
	gettime(&final);
	temp = final - initial;
	printf(" Final Time = %f\n Numbers %d\n", temp, num_threads);
}

