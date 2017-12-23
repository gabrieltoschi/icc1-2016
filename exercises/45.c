#include <stdlib.h>
#include <stdio.h>

int checkMagicSquare(int **magic, int sz){
	int x, y;
	int chk1 = 0, chk2 = 0;
	int sum;

	// checando diagonais
	for (x = 0; x < sz; x++){
		chk1 += magic[x][x];
		chk2 += magic[x][sz-1-x];
	}

	if (chk1 != chk2) return 0;
		else sum = chk1;
	

	// checando linhas e colunas
	for (x = 0; x < sz; x++){
		chk1 = 0;
		chk2 = 0;
		for (y = 0; y < sz; y++){
			chk1 += magic[x][y];
			chk2 += magic[y][x];
		}

		if (chk1 != sum || chk2 != sum) return 0;
	}

	return 1;
}

void freeSqMatrix(int **m, int sz){
	int i;
	for (i = 0; i < sz; i++) free(m[i]);
	free(m);
}

int **readSqMatrix(int sz){
	int i, j;
	int **m;
	m = (int **) malloc(sizeof(int *)*sz);

	for (i = 0; i < sz; i++){
		m[i] = (int *) malloc(sizeof(int)*sz);
		for (j = 0; j < sz; j++){
			scanf("%d", &m[i][j]);
		}
	}

	return m;
}

int main (int argc, char *argv[]){
	int size;
	int **magic;

	scanf("%d", &size);
	magic = readSqMatrix(size);

	if (checkMagicSquare(magic, size)) printf("SIM\n");
		else printf("NAO\n");

	freeSqMatrix(magic, size);
	return 0;
}