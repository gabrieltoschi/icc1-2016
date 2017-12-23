#include <stdio.h>
#include <math.h>

int main (int argc, char *argv[]){

	double x, sen;
	long double pot, fat;
	scanf("%lf", &x);
	int i, op, n;

	fat = 1.0;
	sen = x;
	pot = x;
	op = -1;

	for (i = 0; i < 299; i++){
		n = 3 + 2*i;
		fat = fat * n * (n-1);

		sen += op * (pow(x, n)/fat);
		op *= -1;	
	}

	printf("%.6lf\n", sen);
	return 0;
}