#include <stdlib.h>
#include <stdio.h>

void freeMatrix(int **m, int a){
	int i;
	for (i = 0; i < a; i++) free(m[i]);
	free(m);
}

int **createMatrix(int a, int b){
	int i;
	int **m = (int **) calloc(a, sizeof(int *));
	for (i = 0; i < a; i++){
		m[i] = (int *) calloc(b, sizeof(int));
	}

	return m;
}

int **readMatrix(int a, int b){
	int i, j;
	int **m = createMatrix(a, b);

	for (i = 0; i < a; i++){
		for (j = 0; j < b; j++){
			scanf("%d", &m[i][j]);
		}
	}

	return m;
}

int main (int argc, char *argv[]){

	int ma, mb, na, nb;
	int i, l, k;
	int soma = 0;

	scanf("%d%d", &ma, &mb);
	int **m = readMatrix(ma, mb);

	scanf("%d%d", &na, &nb);
	int **n = readMatrix(na, nb);

	int **r = createMatrix(ma, nb);

	for (l = 0; l < nb; l++){
		for (k = 0; k < ma; k++){
			for (i = 0; i < mb; i++){
				soma = soma + (m[k][i] * n[i][l]);
			}

			r[k][l] = soma;
			soma = 0;	
		}
	}

	for (k = 0; k < ma; k++){
		for (l = 0; l < nb-1; l++){
			printf("%d ", r[k][l]);	
		}
		printf("%d\n", r[k][nb-1]);
	}

	freeMatrix(m, ma);
	freeMatrix(n, na);
	freeMatrix(r, ma);

	return 0;
}