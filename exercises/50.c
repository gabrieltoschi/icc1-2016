#include <stdio.h>

double lucas(double a){
	if (a == 0) return 2;
	else if (a == 1) return 1;
	else return lucas(a-2) + lucas (a-1);
}

int main (int argc, char *argv[]){

	double x;
	scanf("%lf", &x);
	printf("%lf\n", lucas(x));

	return 0;
}