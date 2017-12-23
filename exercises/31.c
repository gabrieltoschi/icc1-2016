#include <stdlib.h>
#include <stdio.h>

int main (int argc, char *argv[]){

	int n, i, j;
	int ct = 0;
	float aux;
	scanf("%d", &n);

	float *seq = (float *) malloc(sizeof(float)*n);
	for (i = 0; i < n; i++){
		scanf("%f", seq+i);
	}

	for (i = 1; i < n; i++){
		for (j = 0; j < n-1; j++){
			if (*(seq+j) > *(seq+j+1)){
				aux = *(seq+j);
				*(seq+j) = *(seq+j+1);
				*(seq+j+1) = aux;
			}
		}
	}

	for (i = 0; i < n; i++){
		if (ct == 0){ // primeiro encontro de um valor
			aux = *(seq+i);
			ct++;
		} else { // checagem de valores iguais
			if (aux == *(seq+i)){ // proximo encontro do mesmo valor
				ct++;
			} else { // novo valor encontrado
				printf("%.1f %d\n", aux, ct);
				aux = *(seq+i);
				ct = 1;
			}
		}
	}

	printf("%.1f %d\n", aux, ct);

	free(seq);
	return 0;
}