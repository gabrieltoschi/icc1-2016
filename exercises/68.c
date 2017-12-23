#include <stdlib.h>
#include <stdio.h>
#include <math.h>

double *jacobsthalLucas(int n){
	double *seq = (double *) calloc(n, sizeof(double));
	int i;

	for (i = 0; i < n; i++){
		if (i > 1) seq[i] = (2*seq[i-2]) + seq[i-1];
		if (i == 0) seq[i] = 2.0;
		if (i == 1) seq[i] = 1.0;
	}

	return seq;
}

void printVector(double *v, int n){
	int i;
	for (i = 0; i < n; i++) printf("%.1lf ", v[i]);
	printf("\n");
}

double average(double *v, int start, int end){
	double avg = 0;
	int i;

	for (i = start; i < end; i++) avg += v[i];
	return avg / ((end - start) * 1.0);
}

double variance(double *v, int n){
	double var = 0, avg = average(v, 0, n);
	int i;

	for (i = 0; i < n; i++)
		var += pow(v[i] - avg, 2);

	var /= n;
	return var;
}

double chebyshev(double *v, int n){
	double dist = 0, aux;
	int i, medium = n / 2;

	for (i = 0; i < medium; i++){
		aux = v[i] - v[medium+i];
		aux = aux < 0 ? (aux * (-1)) : aux;
		dist = aux > dist ? aux : dist;
	}

	return dist;

}

int main (int argc, char *argv[]){
	
	int n, op;
	scanf("%d%d", &op, &n);

	double *sequence = jacobsthalLucas(n);

	switch(op){
		case 1:
			printVector(sequence, n);
			break;
		case 2:
			printf("%.4lf\n", variance(sequence, n));
			break;
		case 3:
			printf("%.4lf\n", chebyshev(sequence, n));
			break;
	}
	
	free(sequence);
	return 0;
}