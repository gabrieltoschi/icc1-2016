#include <stdio.h>

int main (int argc, char *argv[]){

	double n;
	double i;
	double sum = 0;
	scanf("%lf", &n);

	for (i = 0; i < n; i++){
		sum += ((i*2)+1) / (n - i);
	}

	printf("%.4lf\n", sum);
	return 0;
}