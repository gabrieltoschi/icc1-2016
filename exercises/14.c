#include <stdio.h>

int main (int argc, char *argv[]){

	int qtd, i;
	float cons, ant, num;
	scanf("%f%f%d", &ant, &cons, &qtd);

	for (i = 1; i <= qtd; i++){
		num = cons * ant * (1 - ant);
		printf("%d %f\n", i, num);
		ant = num;
	}

	return 0;
}