#include <stdlib.h>
#include <stdio.h>

void hprint(int **table, int *size, int k){
	/** imprime a hash table na tela, mostrando os índices **/
	int i, j;

	for (i = 0; i < k; i++){
		printf("%d:", i);
		if (*(table+i) != NULL){
			for (j = 0; j < *(size+i); j++){
				printf(" %d", *(*(table+i)+j));
			}
		}
		printf("\n");
	}
}

void hinsert(int **table, int *size, int k, int n){
	/** insere um numero n na tabela hash a partir da operação de mod
		com o tamanho k **/

	int index = n % k;

	*(table+index) = (int *) realloc(*(table+index), sizeof(int)*(*(size+index) + 1));
	*(*(table+index) + *(size+index)) = n;
	*(size+index) += 1; 
}

void hfree(int **table, int *size, int k){
	/** libera as regiões da memória heap correspondentes à tabela hash
	e ao vetor que guarda o tamanho de suas linhas **/
	int i;
	free(size);

	for (i = 0; i < k; i++){
		if (*(table+i) != 0){
			free(*(table+i));
		}
	}

	free(table);
}

void hcreate(int ***table, int **size, int k){
	/** aloca as regiões dos ponteiros da tabela hash e 
	a região que guarda o tamanho de cada linha da 
	tabela hash **/
	*(table) = (int **) calloc (k, sizeof(int *));
	*(size) = (int *) calloc(k, sizeof(int));
}

int main (int argc, char *argv[]){

	int k, n, i, aux;
	scanf("%d%d", &k, &n);

	int **table;
	int *size;
	hcreate(&table, &size, k);

	for (i = 0; i < n; i++){
		scanf("%d", &aux);
		hinsert(table, size, k, aux);
	}

	hprint(table, size, k);

	hfree(table, size, k);
	return 0;
}