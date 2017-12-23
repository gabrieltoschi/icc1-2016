#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef enum {
	false,
	true
} bool;

bool isPrime(int n, int ct, int end){
	// condição de parada: todos os números foram testados
	// o número É primo
	if (ct == end) return true;

	// condição de parada: n é divisível por ct
	// o número NÃO É primo
	if (n % ct == 0) return false;

	// passo recursivo: checar com o próximo possível divisor
	return isPrime(n, ct+1, end);
}

int main (int argc, char *argv[]){

	int n, i;
	double sum = 0, op = 1.0;
	scanf("%d", &n);

	for (i = 2; i <= n; i++){
		if (isPrime(i, 2, (int) sqrt(i)+1)){ // é primo
			sum += (1.0/i)*op;
			op *= -1.0;
		}
	}

	printf("%lf\n", sum);
	return 0;
}