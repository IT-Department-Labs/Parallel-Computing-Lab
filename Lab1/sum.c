#include <stdio.h>
#include <stdlib.h>

int main(void){

	int sum;
	int i,N;
	sum=0;
	N=8;

	#pragma omp parallel for reduction(+:sum)	
		for(i=0;i<N;i++){
			sum+=i;
		}
		printf("Sum of numbers: %d\n",sum);
}
