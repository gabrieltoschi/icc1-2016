#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int otherPoint (int a, int b, int max){
	int i;
	for (i = 0; i < max; i++) if (a != i && b != i) return i;
	return -1;
}

double distance(double x1, double y1, double x2, double y2){
	double parc1 = pow((x1 - x2), 2);
	double parc2 = pow((y1 - y2), 2);
	return sqrt(parc1 + parc2);
}

int main(int argc, char *argv[])
{
	int n, i, j, other;
	double *x, *y;
	double **dist;
	double xi, yi, answer = -1;
	
	scanf("%d", &n);
	scanf("%lf%lf", &xi, &yi);

	x = (double *) malloc(sizeof(double)*(n-1));
	y = (double *) malloc(sizeof(double)*(n-1));
	dist = (double **) malloc(sizeof(double *)*(n-1));

	for(i = 0; i < n-1; i++){
		scanf("%lf%lf", &x[i], &y[i]);
		dist[i] = (double *) calloc(n-1, sizeof(double));
		for (j = 0; j < n-1; j++) dist[i][j] += distance(xi, yi, x[i], y[i]);
	}

	for (i = 0; i < n-1; i++){
		for (j = 0; j < n-1; j++){
			if (i != j){
				dist[i][j] += distance(x[i], y[i], x[j], y[j]);
				other = otherPoint(i, j, n-1);
				dist[i][j] += distance(x[j], y[j], x[other], y[other]);
				dist[i][j] += distance(x[other], y[other], xi, yi);

				if (dist[i][j] < answer || answer == -1) answer = dist[i][j];
			}
		}
	}

	printf("%lf\n", answer);

	for (i = 0; i < n-1; i++) free(dist[i]);
	free(dist);

	return 0;
}