#include <stdio.h>

int main (int argc, char *argv[]){

	int i;
	double n;
	double soma = 0;

	scanf("%lf", &n);

	for (i = 1; i <= n; i++){
		soma += i / (n - i + 1);
	}

	printf("%.4lf\n", soma);

	return 0;
}