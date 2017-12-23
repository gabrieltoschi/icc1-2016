#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
// limits.h é incluído para ter a definição de INT_MAX (o maior número armazenado por um int),
// utilizado na função checkMaxMin

/**** DEFINIÇÕES E ESTRUTURAS ****/
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

/**** FUNÇÕES AUXILIARES: STRINGS ****/
char *readString(FILE *stream, char delim){
	/** lê uma string até um Enter e armazena na memória Heap **/
	char *str = NULL;
	char c;
	int ct = 0;

	do {
		c = fgetc(stream);
		str = (char *) realloc(str, sizeof(char)*(ct+1));
		str[ct++] = c;
	} while (c != delim);

	str[--ct] = '\0';
	return str;
}

char *copyString(char *string){
	/** copia uma string para outra região da memória Heap, já alocando
		a memória necessária **/
	char *new = (char *) malloc(sizeof(char)*(strlen(string)+1));
	strcpy(new, string);
	return new;
}

/**** FUNÇÕES AUXILIARES: MATRIZES ****/
int **allocIntMatrix(int width, int height){
	/** aloca uma matriz de inteiros na memória Heap **/
	int i;
	int **m = (int **) malloc(sizeof(int *)*height);

	for (i = 0; i < height; i++)
		m[i] = (int *) malloc(sizeof(int)*width);

	return m;
}

double **allocDoubleMatrix(int width, int height){
	/** aloca uma matriz de números reais na memória Heap **/
	int i;
	double **m = (double **) malloc(sizeof(double *)*height);

	for (i = 0; i < height; i++)
		m[i] = (double *) malloc(sizeof(double)*width);

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

double **readDoubleMatrix(FILE *stream, int width, int height){
	/** lê, a partir de um arquivo, valores reais e os armazena em uma matriz **/
	double **m = allocDoubleMatrix(width, height);
	int i, j;
	for (i = 0; i < height; i++){
		for (j = 0; j < width; j++){
			fscanf(stream, "%lf", &m[i][j]);
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

/**** FUNÇÕES AUXILIARES: INTEIROS ****/
int isInside(int row, int col, int width, int height){
	/** verifica se uma coordenada está dentro dos limites de uma matriz, 
		a partir do seu tamanho **/
		if (row < 0 || col < 0 || row >= height || col >= width) return false;
			else return true;
}

void checkMaxMin(int *max, int *min, int new){
	/** usado na iteração de uma sequência de números, verifica o maior
	e o menor entre eles **/
		if (new > *max) *max = new;
		if (new < *min) *min = new;
}

int normalize(int maxValue, int conv, int convMin, int convMax){
	/** faz os cálculos necessários para normalizar o valor de um pixel de
	um arquivo PGM após a convolução **/
	int aux1 = conv - convMin;
	aux1 *= maxValue;
	int aux2 = convMax - convMin;
	int aux3 = aux1 / aux2;
	return aux3;
}

/**** FUNÇÕES DE MANIPULAÇÃO DE PGM ****/
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

PGM PGMcreate(PGM model){
	/** cria uma nova imagem PGM em branco a partir dos atributos básicos
	de uma outra imagem PGM **/
	PGM new;
	new.magicNumber = copyString(model.magicNumber);
	new.width = model.width;
	new.height = model.height;
	new.maxValue = model.maxValue;
	new.pixels = allocIntMatrix(model.width, model.height);

	return new;
}

PGM PGMnegative(PGM image){
	/** gera o negativo de uma imagem PGM e retorna como uma nova imagem **/
	PGM result;
	int i, j;

	// preparação da nova imagem PGM
	result = PGMcreate(image);

	// corre por cada pixel da matriz
	for (i = 0; i < image.height; i++){
		for (j = 0; j < image.width; j++){
			// retira, do valor máximo, o valor de cada pixel, conseguindo seu negativo
			result.pixels[i][j] = image.maxValue - image.pixels[i][j];
		}
	}

	return result;
}

void PGMnormalize(PGM image, int max, int min){
	/** normaliza todos os pixels de uma imagem PGM após uma operação de convolução **/
	int i, j;
	for (i = 0; i < image.height; i++){
		for (j = 0; j < image.width; j++){
			image.pixels[i][j] = normalize(image.maxValue, image.pixels[i][j], min, max);
		}
	}
}

PGM PGMmasking(PGM image, double **mask, int maskSize){
	/** aplica uma máscara de números reais em uma imagem PGM, a partir de uma operação
	de convolução de matrizes **/
	PGM result;
	int i, j, k, l;
	int convMax = 0, convMin = INT_MAX;
	int conversion = maskSize / 2;

	// preparação da nova imagem PGM
	result = PGMcreate(image);

	for (i = 0; i < image.height; i++){
		for (j = 0; j < image.width; j++){
			result.pixels[i][j] = 0;
			// laços de convolução começam em números negativos para representar uma
			// 											"expansão virtual" da matriz
			for (k = conversion*-1; k <= conversion; k++){
				for (l = conversion*-1; l <= conversion; l++){
					// checa se o pixel a ser checado está dentro dos limites da matrix
					if (isInside(k+i, j+l, image.width, image.height)){
						result.pixels[i][j] += (int) image.pixels[k+i][j+l] *
								mask[k+(k*(-2))+conversion][l+(l*(-2))+conversion];
					}
				}
			}
			checkMaxMin(&convMax, &convMin, result.pixels[i][j]);
		}
	}

	PGMnormalize(result, convMax, convMin);
	return result;
}

/**** FUNÇÕES DE MANIPULAÇÃO DE MÁSCARAS ****/
double **readMask(char *filename, int *size){
	/** lê uma máscara de manipulação das máscaras a partir de um arquivo **/
	double **mask;
	FILE *fp = fopen(filename, "r");

	fscanf(fp, "%d", size);
	mask = readDoubleMatrix(fp, *size, *size);
	fclose(fp);
	return mask;
}

int main(int argc, char *argv[]){

	int op, maskSize;
	char *imageFilename, *maskFilename;
	PGM image, result;
	double **mask;

	scanf("%d", &op);
	fgetc(stdin);
	imageFilename = readString(stdin, '\n');

	image = PGMread(imageFilename);

	// checagem de operação (1: negativo | 2: filtragem espacial)
	switch(op){
		case 1:
			result = PGMnegative(image);
			break;
		case 2:
			maskFilename = readString(stdin, '\n');
			mask = readMask(maskFilename, &maskSize);
			result = PGMmasking(image, mask, maskSize);
			free(maskFilename);
			freeMatrix((void *) mask, maskSize);
			break;
	}

	PGMprint(result);

	free(imageFilename);
	PGMfree(image);
	PGMfree(result);

	return 0;
}