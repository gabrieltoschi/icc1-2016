//	MAP MODEL
//  FEDCBA9876543210

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>

#define MATRIXSIZE 16
#define true 1
#define false 0

typedef unsigned short map;
typedef struct {
	int *pos;
	int posct;
	int r;
	int c;
} prob;

enum {
	ROW,   // 0
	COL,   // 1
	BOX,   // 2
	NINST  // 3 
};

void freeDoubleMatrix(void **m, int size){
	int i;
	for (i = 0; i < size; i++) free(m[i]);
	free(m);
}

char *readString(){
	char *str = NULL;
	char c;
	int ct = 0;

	do {
		scanf("%c", &c);
		str = (char *) realloc(str, sizeof(char)*(ct+1));
		*(str+ct) = c;
		ct++;
	} while (c != '\n');

	ct--;
	*(str+ct) = '\0';
	return str;
}

char **allocMat(int c, int r){
	int i;
	char **m = (char **) malloc(sizeof(char *)*r);
	for (i = 0; i < r; i++) m[i] = (char *) malloc(sizeof(char)*c);
	return m;
}

char **readMat(char *path, int *c, int *r){
	int i, j;
	*c = MATRIXSIZE;
	*r = MATRIXSIZE;
	FILE *fp = fopen(path, "r");
	char **m = allocMat(*c, *r);

	for (i = 0; i < *r; i++){
		for (j = 0; j < *c; j++){
			m[i][j] = fgetc(fp);
		}
		fgetc(fp);
	}

	fclose(fp);
	return m;

}

void printMat(char **mat, int c, int r){
	int i, j;
	for (i = 0; i < r; i++){
		for (j = 0; j < c; j++){
			printf("%c", mat[i][j]);
		}
		printf("\n");
	}
}

map **allocMaps(int n){
	int i, j;
	map **m;

	m = (map **) malloc(sizeof(map)*NINST);
	for (i = 0; i < NINST; i++){
		m[i] = (map *) calloc(n, sizeof(map));
	}

	return m;
}

int hexaToInt(char c){
	if (isdigit(c)) return (int) c-48;
	else if (isalpha(c)) return toupper(c)-55;
	else return -1;
}

char intToHexa(int n){
	if (n <= 9) return (char) n+48;
	else if (n <= 15) return (char) n+55;
	else return -1;
}

map fillMapUnitHexa(map m, char f){
	return m | (1 << hexaToInt(f));
}

map fillMapUnitInt(map m, int f){
	return m | (1 << f);
}

int getBox(int r, int c, int boxsize){
	return ((r/boxsize)*boxsize) + (c/boxsize);
}

map **createMaps(char **sudoku, int n, prob **p, int *pct, unsigned char **ts){
	map **maps = allocMaps(n);
	prob *pro = NULL;
	unsigned char *toSolve = NULL;
	int i, j, box, pcount = 0;
	int boxsize = sqrt(n);

	for (i = 0; i < n; i++){
		for (j = 0; j < n; j++){
			if (sudoku[i][j] != '.'){
				box = getBox(i, j, boxsize);
				maps[ROW][i]   = fillMapUnitHexa(maps[ROW][i],   sudoku[i][j]);
				maps[COL][j]   = fillMapUnitHexa(maps[COL][j],   sudoku[i][j]);
				maps[BOX][box] = fillMapUnitHexa(maps[BOX][box], sudoku[i][j]);
			} else {
				pro = (prob *) realloc(pro, sizeof(prob)*(pcount+1));
				toSolve = (unsigned char *) realloc(toSolve, sizeof(unsigned char)*(pcount+1));
				toSolve[pcount] = pcount;
				pro[pcount].pos = NULL;
				pro[pcount].posct = 0;
				pro[pcount].r = i;
				pro[pcount++].c = j;
			}
		}
	}

	*p = pro;
	*pct = pcount;
	*ts = toSolve;
	return maps;
}

int isPossible(int n, map m){
	if ((m & 1 << n) == 0) return 1;
	else return 0;
}

int *takePossibles(int n, map **maps, int r, int c, int *possiblect){
	int i;
	int boxsize = sqrt(n);
	int *possibles = NULL;
	for (i = 0; i < n; i++){
		if (isPossible(i, maps[ROW][r]) &&
			isPossible(i, maps[COL][c]) &&
			isPossible(i, maps[BOX][getBox(r, c, boxsize)])){
			possibles = (int *) realloc(possibles, sizeof(int)*((*possiblect)+1));
			possibles[(*possiblect)++] = i;
		}
	}

	return possibles;
}

void updatePossibles(int n, map **maps, int r, int c, int* toUpdate, int *possiblect){
	int i;
	int boxsize = sqrt(n);
	int newpossibct = 0;
	for (i = 0; i < *possiblect; i++){
		if (isPossible(toUpdate[i], maps[ROW][r]) &&
			isPossible(toUpdate[i], maps[COL][c]) &&
			isPossible(toUpdate[i], maps[BOX][getBox(r, c, boxsize)])){
			toUpdate[newpossibct++] = toUpdate[i];
		}

	}
	*possiblect = newpossibct;
}

void solutionFound(int size, char **sudoku, map **maps, int r, int c, int num){
	int box, boxsize = sqrt(size);

	// atualizar o sudoku
	sudoku[r][c] = intToHexa(num);

	// atualizar mapas
	box = getBox(r, c, boxsize);
	maps[ROW][r]   = fillMapUnitInt(maps[ROW][r],   num);
	maps[COL][c]   = fillMapUnitInt(maps[COL][c],   num);
	maps[BOX][box] = fillMapUnitInt(maps[BOX][box], num);

	//printf(">> solved! %d, %d\n", r, c);
}

void solveSudoku(char **sudoku, map **maps, int n, prob *p, int pct, unsigned char *toSolve){
	int i, newpct, current;
	int test = 0;

	while (pct != 0){
	//for (test = 0; test < 10; test++){
		//printf("|||iteracao %d|||\n", test);
		newpct = 0;
		for (i = 0; i < pct; i++){
			current = toSolve[i];
			if (p[current].pos == NULL){ // deve ser feita 1ª seleção dos numeros possiveis
				p[current].pos = takePossibles(n, maps, p[current].r, p[current].c, &p[current].posct);
				if (p[current].posct == 1){
					solutionFound(n, sudoku, maps, p[current].r, p[current].c, p[current].pos[0]);
					free(p[current].pos);
				}
				else toSolve[newpct++] = current;
			} else { // atualizar situação dos números possíveis
				updatePossibles(n, maps, p[current].r, p[current].c, p[current].pos, &p[current].posct);
				if (p[current].posct == 1){
					solutionFound(n, sudoku, maps, p[current].r, p[current].c, p[current].pos[0]);
					free(p[current].pos);
				}
				else toSolve[newpct++] = current;
			}
		}
		pct = newpct;
		//printf(">>> pct = %d\n", pct);
		test++;
	}
}

int main (int argc, char *argv[]){

	int rows, cols, probcount;
	unsigned char *toSolve;
	char **sudoku;
	map **maps;
	prob *probs;

	//char *filename = readString();
	char filename[8];
	scanf("%s", filename);
	sudoku = readMat(filename, &cols, &rows);
	//free(filename);
	maps = createMaps(sudoku, rows, &probs, &probcount, &toSolve);
	
	//printf("%hu\n", maps[BOX][0]);
	

	solveSudoku(sudoku, maps, rows, probs, probcount, toSolve);

	/*int i;
	for (i = 0; i < probcount; i++){
		printf("%d: l[%d], c[%d], p[%d]\n", toSolve[i], probs[i].r, probs[i].c, probs[i].posct);
	}*/
	printMat(sudoku, rows, cols);

	freeDoubleMatrix((void *) sudoku, rows);
	freeDoubleMatrix((void *) maps, NINST);
	free(probs);
	free(toSolve);
	return 0;
}