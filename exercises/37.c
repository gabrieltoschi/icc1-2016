#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main (int argc, char *argv[]){

	float n;
	int i;
	double media = 0;
	double desvio = 0;
	scanf("%f", &n);

	double *num = (double *) malloc(sizeof(double)*n);
	for (i = 0; i < n; i++){
		scanf("%lf", num+i);
		media += num[i];
	}

	media /= n;

	for (i = 0; i < n; i++){
		desvio += pow((num[i] - media), 2);
	}
	
	desvio /= n;
	desvio = sqrt(desvio);

	printf("%.4lf\n%.4lf\n", media, desvio);

	free(num);
	return 0;
}