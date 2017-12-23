#include <stdio.h>

int main (int argc, char *argv[]){

	int n, i;
	scanf("%d", &n);

	float nota;
	float media = 0;
	for (i = 0; i < n; i++){
		scanf("%f", &nota);
		media += 1 / (nota + 1);
	}

	media = (n / media) - 1;
	printf("%.2f\n", media);

	return 0;
}