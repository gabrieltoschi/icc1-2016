#include <stdlib.h>
#include <stdio.h>
#include <math.h>

double *tribonacci(int n){
	double *seq = (double *) calloc(n, sizeof(double));
	int i;

	for (i = 0; i < n; i++){
		if (i > 2) seq[i] = seq[i-3] + seq[i-2] + seq[i-1];
		if (i == 0) seq[i] = 0.0;
		if (i == 1) seq[i] = 0.0;
		if (i == 2) seq[i] = 1.0;
	}

	return seq;
}

void printVector(double *v, int n){
	int i;
	for (i = 0; i < n; i++) printf("%.1lf ", v[i]);
	printf("\n");
}

double average(double *v, int start, int end, int size){
	double avg = 0;
	int i;

	for (i = start; i < end; i++) avg += v[i];
	return avg / (size * 1.0);
}

double pearson(double *v, int n){
	int i, medium = n / 2;

	double avgL = average(v, 0, medium, medium);
	double avgR = average(v, medium, n, medium);
	double cov = 0, varL = 0, varR = 0, var;

	for (i = 0; i < medium; i++){
		cov += (v[i] - avgL) * (v[medium+i] - avgR);
		varL += (v[i] - avgL) * (v[i] - avgL);
		varR += (v[medium+i] - avgR) * (v[medium+i] - avgR);
	}

	var = varL * varR;
	var = sqrt(var);
	cov /= var;
	return cov;
}

int main (int argc, char *argv[]){
	
	int n, op;
	scanf("%d%d", &op, &n);

	double *sequence = tribonacci(n);

	switch(op){
		case 1:
			printVector(sequence, n);
			break;
		case 2:
			printf("%.4lf\n", average(sequence, 0, n, n));
			break;
		case 3:
			printf("%.4lf\n", pearson(sequence, n));
			break;
	}
	
	free(sequence);
	return 0;
}