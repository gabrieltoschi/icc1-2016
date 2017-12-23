#include <stdio.h>

int main (int argc, char *argv[]){

	int n;
	scanf("%d", &n);

	double sum = 0;
	int op = 1;

	double i;

	for (i = 1; i <= n; i++){
		if (op == 1){
			sum = sum + (1/i);
			op = 0;
		} else {
			sum = sum - (1/i);
			op = 1;
		}
	}

	printf("%.4lf\n", sum);
	return 0;
}