#include <stdlib.h>
#include <stdio.h>
#include <math.h>

double *tetranacci(int n){
	double *seq = (double *) calloc(n, sizeof(double));
	int i;

	for (i = 0; i < n; i++){
		if (i > 3)  seq[i] = seq[i-4] + seq[i-3] + seq[i-2] + seq[i-1];
		if (i == 0) seq[i] = 0.0;
		if (i == 1) seq[i] = 0.0;
		if (i == 2) seq[i] = 1.0;
		if (i == 3) seq[i] = 1.0;
	}

	return seq;
}

void printVector(double *v, int n){
	int i;
	for (i = 0; i < n; i++) printf("%.1lf ", v[i]);
	printf("\n");
}

double quadAverage(double *v, int n){
	double avg = 0;
	int i;

	for (i = 0; i < n; i++) avg += v[i]*v[i];
	avg /= (n * 1.0);

	return sqrt(avg);
}

double manhattan(double *v, int n){
	double dist = 0, aux;
	int i, medium = n / 2;

	for (i = 0; i < medium; i++){
		aux = v[i] - v[medium+i];
		dist += aux < 0 ? (aux * (-1)) : aux;
	}

	return dist;
}

int main (int argc, char *argv[]){
	
	int n, op;
	scanf("%d%d", &op, &n);

	double *sequence = tetranacci(n);

	switch(op){
		case 1:
			printVector(sequence, n);
			break;
		case 2:
			printf("%.4lf\n", quadAverage(sequence, n));
			break;
		case 3:
			printf("%.4lf\n", manhattan(sequence, n));
			break;
	}
	
	free(sequence);
	return 0;
}