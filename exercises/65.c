#include <stdlib.h>
#include <stdio.h>

typedef enum {
	false,
	true
} bool;

char* readString(FILE *stream, char delim){
	char *str = NULL;
	int ct = 0;
	char c;

	do {
		c = fgetc(stream);
		str = (char *) realloc(str, sizeof(char)*(ct+1));
		str[ct++] = c;
	} while (c != delim && c != EOF);

	str[--ct] = '\0';
	return str;
}

int countToken(char *filename, char token, char end){
	char c;
	int counter = 0;
	FILE *stream = fopen(filename, "r");

	do {
		c = fgetc(stream);
		if (c == token) counter++; 
	} while (c != end);

	fclose(stream);
	return counter;
}

double **readSqMat(char *filename, int size){
	int i, j;
	FILE *fp = fopen(filename, "r");

	double **m = (double **) malloc(sizeof(double *)*size);
	for (i = 0; i < size; i++) {
		m[i] = (double *) malloc(sizeof(double)*size);
		for (j = 0; j < size; j++) fscanf(fp, "%lf", &m[i][j]);
	}

	fclose(fp);
	return m;
}

void freeMat(void **m, int n){
	int i;
	for (i = 0; i < n; i++) free(m[i]);
	free(m);
}

void printMat(double **mat, int c, int r){
	int i, j;
	for (i = 0; i < r; i++){
		for (j = 0; j < c; j++){
			printf("%.4lf ", mat[i][j]);
		}
		printf("\n");
	}
}

double oneNorm(double **m, int n){
	int i, j;
	double cur, max = 0;

	for (i = 0; i < n; i++){
		cur = 0;
		for (j = 0; j < n; j++) cur += m[j][i];
		if (cur > max) max = cur;
	}

	return max;
}

double **sumMat(double **A, double **B, int size){
	int i, j;
	double **s = (double **) malloc(sizeof(double *)*size);
	for (i = 0; i < size; i++){
		s[i] = (double *) malloc(sizeof(double)*size);
		for (j = 0; j < size; j++) s[i][j] = A[i][j] + B[i][j];
	}

	return s;
}

int main (int argc, char *argv[]){
	char *file1 = readString(stdin, '\n');
	char *file2 = readString(stdin, '\n');
	int matSize = countToken(file1, '.', '\n');

	double **A = readSqMat(file1, matSize);
	double **B = readSqMat(file2, matSize);

	printf("%.4lf\n", oneNorm(A, matSize));
	printf("%.4lf\n", oneNorm(B, matSize));

	double **S = sumMat(A, B, matSize);
	printMat(S, matSize, matSize);
	printf("%.4lf\n", oneNorm(S, matSize));

	free(file1);
	free(file2);
	freeMat((void *) A, matSize);
	freeMat((void *) B, matSize);
	freeMat((void *) S, matSize);
	return 0;
}