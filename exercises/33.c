#include <stdlib.h>
#include <stdio.h>

int main (int argc, char *argv[]){

	long long int n;
	int i;
	int ct = 0;
 
	char *algs = (char *) malloc(sizeof(char)*16);
	for (i = 0; i < 10; i++){
		*(algs+i) = '0' + i;
	}
	for (i = 10; i < 16; i++){
		*(algs+i) = 'A' + i-10;
	}

	scanf("%lld", &n);
	char *hexa = NULL;

	while (n != 0){
		hexa = (char *) realloc(hexa, sizeof(char)*(ct+1));
		*(hexa+ct) = *(algs+(n % 16));
		ct++;
		n -= n % 16;
		n /= 16;
	}

	for (i = ct-1; i >= 0; i--){
		printf("%c", *(hexa+i));
	}

	printf("\n");

	free(algs);
	free(hexa);
	return 0;
}