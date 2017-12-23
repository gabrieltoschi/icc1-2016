#include <stdlib.h>
#include <stdio.h>
#include <math.h>

double onlineAverage(double prevavg, double n, int ct){
	return prevavg + ((n - prevavg)/ct);
}

double onlineVariance(double prevvar, double xn, double prevavg, int n){
	double parc1, parc2, res;
	parc1 = (n-2)*prevvar;
	parc1 /= (n-1);
	parc2 = pow((xn - prevavg), 2);
	parc2 /= n;
	res = parc1 + parc2;
	return res;
}

int main(int argc, char *argv[])
{
	double *avg = (double *) malloc(sizeof(double)*1);;
	double *var = (double *) malloc(sizeof(double)*1);;
	double *n = (double *) malloc(sizeof(double)*2);
	double new;
	int nct = 2, rct = 1, i;

	scanf("%lf", &n[0]);
	scanf("%lf", &n[1]);
	avg[0] = (n[0] + n[1])/2;
	var[0] = pow((n[0] - avg[0]), 2) + pow((n[1] - avg[0]), 2);

	while (scanf("%lf", &new) != EOF){
		n = (double *) realloc(n, sizeof(double)*(nct+1));
		n[nct] = new;

		avg = (double *) realloc(avg, sizeof(double)*(rct+1));
		var = (double *) realloc(var, sizeof(double)*(rct+1));
		var[rct] = onlineVariance(var[rct-1], new, avg[rct-1], nct+1);
		avg[rct] = onlineAverage(avg[rct-1], new, nct+1);

		nct++;
		rct++;
	}

	for (i = 0; i < rct; i++){
		printf("%.2lf ", avg[i]);
	}
	printf("\n");
	for (i = 0; i < rct; i++){
		printf("%.2lf ", var[i]);
	}
	printf("\n");

	return 0;
}