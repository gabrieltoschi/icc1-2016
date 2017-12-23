#include <stdio.h>

void swap(int *a, int *b){
	int *aux;

	if (a < b){
		aux = a;
		a = b;
		b = aux;
	}
}

int mdc(int a, int b){
	if (b == 0) return a;
	return mdc(b, a%b);
}

int mmc(int a, int b){
	if (b == 0) return a;
	else return (a*b) / mdc(a, b);
}

int main (int argc, char *argv[]){

	int x, y;
	scanf("%d%d", &x, &y);
	swap(&x, &y);

	printf("%d\n", mmc(x, y));
	return 0;
}