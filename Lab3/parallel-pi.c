#include <stdio.h>

int main(int argc, char const *argv[])
{
	double pi, x;
	int i, N;

	pi = 0.0;
	N = 1000;

	#pragma omp parallel for private(x) reduction(+:pi) 
		for(i = 0; i < N; i ++) {
			x = (double)i/N;
			pi += 4/(1+x*x);
		}

	pi = pi/N;
	printf("%f\n",pi);

	return 0;
}