#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main(int argc, char *argv[])
{
	int k, newmax, max, i, j, check;
	double sk;
	int *crivo;

	scanf("%d", &k);
	crivo = (int *) malloc(sizeof(int)*(--k));
	max = k;
	sk = (double) k;
	sk = floor(sqrt(sk));
	check = (int) sk;

	for (i = 0; i < k; i++){
		crivo[i] = i+2;
		printf("%d ", crivo[i]);
	}
	printf("\n");

	for (i = 0; crivo[i] <= check; i++){
		newmax = 0;
		for (j = 0; j < max; j++){
			if (crivo[j] % crivo[i] != 0 || crivo[j] == crivo[i]){ // nao e' multiplo
				crivo[newmax++] = crivo[j];
				printf("%d ", crivo[j]);
			}
		}
		max = newmax;
		printf("\n");
	}

	return 0;
}