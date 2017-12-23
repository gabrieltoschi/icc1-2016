#include <stdlib.h>
#include <stdio.h>

/** valores booleanos **/
#define true 1
#define false 0

/** estrutura que armazena todos os dados referentes a uma imagem PGM **/
typedef struct {
	char *magicNumber;
	int height;
	int width;
	int maxValue;
	int **pixels;
} PGM;

char *readString(FILE *stream, char delim){
	/** lê uma string até um Enter e armazena na memória Heap **/
	char *str = NULL;
	char c;
	int ct = 0;

	do {
		c = fgetc(stream);
		str = (char *) realloc(str, sizeof(char)*(ct+1));
		str[ct++] = c;
	} while (c != delim && c != EOF);

	str[--ct] = '\0';
	return str;
}

int **allocIntMatrix(int width, int height){
	/** aloca uma matriz de inteiros na memória Heap **/
	int i;
	int **m = (int **) malloc(sizeof(int *)*height);

	for (i = 0; i < height; i++)
		m[i] = (int *) malloc(sizeof(int)*width);

	return m;
}

int **readIntMatrix(FILE *stream, int width, int height){
	/** lê, a partir de um arquivo, valores inteiros e os armazena em uma matriz **/
	int **m = allocIntMatrix(width, height);
	int i, j;
	for (i = 0; i < height; i++){
		for (j = 0; j < width; j++){
			fscanf(stream, "%d", &m[i][j]);
		}
	}

	return m;
}

void printIntMatrix(int **m, int width, int height){
	/** imprime na saída padrão uma matriz de inteiros **/
	int i, j;
	for (i = 0; i < height; i++){
		for (j = 0; j < width; j++){
			printf("%d ", m[i][j]);
		}
		printf("\n");
	}
}

void freeMatrix(void **m, int height){
	/** libera uma matriz alocada na memória Heap **/
	int i;
	for (i = 0; i < height; i++) free(m[i]);
	free(m);
}

void PGMcomment(FILE *stream, char token, char end){
	/** checa a existência de comentário em uma imagem PGM e ignora-o na leitura,
	alterando a posição do cursor **/
	char test = fgetc(stream);
	if (test == token) while (test != end) test = fgetc(stream);
		else ungetc(test, stream);
}

PGM PGMread (char *filename){
	/** lê os dados de um arquivo PGM e o armazena em uma estrutura de dados
	do tipo PGM, a partir do nome do arquivo **/
	PGM image;
	FILE *fp = fopen(filename, "r");

	image.magicNumber = readString(fp, '\n');
	PGMcomment(fp, '#', '\n');
	fscanf(fp, "%d", &image.width);
	fscanf(fp, "%d", &image.height);
	fscanf(fp, "%d", &image.maxValue);
	image.pixels = readIntMatrix(fp, image.width, image.height);

	fclose(fp);
	return image;
}

void PGMprint(PGM image){
	/** imprime, na saída padrão, dados de um arquivo PGM no formato convencional
	da extensão **/
	printf("%s\n", image.magicNumber);
	printf("%d %d\n", image.width, image.height);
	printf("%d\n", image.maxValue);
	printIntMatrix(image.pixels, image.width, image.height);
}

void PGMfree(PGM image){
	/** libera os dados armazenados em memória Heap de uma estrutura de arquivo PGM **/
	free(image.magicNumber);
	freeMatrix((void *) image.pixels, image.height);
}

void printNumRepeat(int num, int repeat, FILE *output){
	int i;

	for (i = 0; i < repeat; i++) fprintf(output, "%d ", num); 
}

void printRunLength(int num, int counter, char token, FILE *output){
	if (counter > 3) fprintf(output, "%c %d %d ", token, num, counter);
		else printNumRepeat(num, counter, output);
}

void PGMrunLength(PGM image, FILE *output, char token){
	int i, j;
	int current, counter = 0;

	fprintf(output, "P8\n");
	fprintf(output, "%d %d\n", image.width, image.height);
	fprintf(output, "%d\n", image.maxValue);

	for (i = 0; i < image.height; i++){
		current = -1;
		for (j = 0; j < image.width; j++){
			if (image.pixels[i][j] == current) counter++;
			else if (current == -1) {
				current = image.pixels[i][j];
				counter = 1;
			}
			else {
				printRunLength(current, counter, token, output);
				current = image.pixels[i][j];
				counter = 1;
			}
		}
		printRunLength(current, counter, token, output);
		fprintf(output, "\n");
	}
}

int main (int argc, char *argv[]){
	char *filename = readString(stdin, '\n');
	PGM image = PGMread(filename);

	PGMrunLength(image, stdout, '@');

	free(filename);
	PGMfree(image);
}