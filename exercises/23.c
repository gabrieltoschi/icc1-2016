#include <stdio.h>
#include <math.h>

int main (int argc, char *argv[]){

	double a1, q, n, an, sn;
	scanf("%lf%lf%lf", &a1, &q, &n);

	an = a1 * (pow(q, (n-1)));
	sn = (a1 * (pow(q, n) - 1)) / (q - 1);

	printf("%.2lf\n%.2lf\n", an, sn);
	return 0;
}