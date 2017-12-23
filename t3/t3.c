#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int search(unsigned int *v, int size, char *m){
	/** busca e conta, na mensagem, quantas ocorrências ocorrem 
		da string m **/
	char *str = (char *) v;
	int matchsize = strlen(m);
	int match; // caracteres iguais em cada iteração do for
	int res = 0; // número de ocorrências de m
	int i, j;

	for (i = 0; i < size-matchsize; i++){
		match = 0;
		for (j = 0; j < matchsize; j++){
			if (*(str+i+j) == *(m+j)){
				match++;
			} else {
				break;
			}
		}

		if (match == matchsize){
			res++;
		}
	}

	return res;
}

void printMessage(unsigned int *v, int size){
	/** a partir do tamanho (em bytes) de um vetor de unsigned ints, ele
		imprime os caracteres correspondentes a cada byte **/

	char *cursor = (char *) v;
	int i;

	for (i = 0; i < size; i++){
		if (*(cursor+i) != '\0'){
			printf("%c", *(cursor+i));
		}
	}

	printf("\n");
}

int verifyValidity(unsigned int *n){
	/** checa a validade dos bytes de cada unsigned int, ou seja, se representam
		caracteres válidos **/
	char *cursor = (char *) n;
	int charNumber = sizeof(unsigned int) / sizeof(char);
	int validity = 0;
	int i;

	for (i = 0; i < charNumber; i++){
		if (((*(cursor+i) >= 48) && (*(cursor+i) <= 57)) || // números
		   ((*(cursor+i) >= 65) && (*(cursor+i) <= 90)) || // letras maiúsculas
		   ((*(cursor+i) >= 97) && (*(cursor+i) <= 122)) || // letras minúsculas
		   ((*(cursor+i) >= 40) && (*(cursor+i) <= 41)) || // parênteses
		   ((*(cursor+i) >= 32) && (*(cursor+i) <= 33)) || // espaço/ponto de exclamação
		   (*(cursor+i) == 44) || // vírgula
		   (*(cursor+i) == 46) || // ponto
		   (*(cursor+i) == 58) || // dois-pontos
		   (*(cursor+i) == 63) || // ponto de interrogação
		   (*(cursor+i) == 0)) { // \0
		   		validity++;
		   }
	}

	if (validity == charNumber){
		return 1;
	} else {
		return 0;
	}
}

void shiftDecrypt(unsigned int *v, int size){
	/** percorre o vetor procurando unsigned ints inválidos para
		shiftá-los novamente e descriptografá-los **/
	int i;

	for (i = 0; i < size; i++){
		if (verifyValidity(v+i) == 0){
			*(v+i) = *(v+i) >> 1;
		}
	}
}

int catchDigit(unsigned int n, int k){
	/** retorna um dígito de um número inteiro em uma posição k, 
		contando da direita para a esquerda **/
	unsigned int aux;
	int i;

	// pega o último digito usando mod, subtrai-ele do número e divide
	// por 10, para fazer a operação novamente, com o próximo dígito
	for (i = 0; i <= k; i++){
			aux = n % 10;
			n -= aux;
			n /= 10;
	}

	return aux;
}

int *digitMapping(unsigned int *v, int size, int k){
	/** percorre os números de um vetor em busca dos dígitos
		que formam o "código secreto" **/
	int i;
	int ct = 0;
	int *map = NULL;

	// encontra os dígitos correspondentes aos códigos e aloca
	// eles em um vetor na memória Heap
	for (i = 0; i < size; i++){
		k = catchDigit(*(v+i), k);
		map = (int *) realloc (map, sizeof(int)*(ct+1));
		*(map+ct) = k;
		ct++;
	}

	return map;
}

void inverseVector(unsigned int *vector, int size){
	/** inverte as posições de um vetor de unsigned ints a partir de seu tamanho **/
	int middle = (size--) / 2;
	unsigned int aux = NULL;
	int i = NULL;

	// troca os valores de posições equidistantes de lugar
	for (i = 0; i < middle; i++){
		aux = *(vector+i);
		*(vector+i) = *(vector+size-i);
		*(vector+size-i) = aux;
	}

	return;
}

int getFileSize(FILE *f){
	/** retorna o tamanho (em bytes) de um arquivo **/
	int currentSize, fileSize;

	// currentSize guarda a posição atual do arquivo para colocá-lo
	// novamente nessa posição após o uso da função
	currentSize = ftell(f);

	// leva o cursor até o final do arquivo e usa ftell para saber
	// quantos bytes existem entre o inicio e o final
	fseek(f, 0, SEEK_END);
	fileSize = ftell(f);

	// leva o arquivo novamente ao local original
	fseek(f, currentSize, SEEK_SET);

	return fileSize;
}

char *readString(){
	/** lê uma string até um Enter e armazena na memória Heap **/
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

int main (int argc, char *argv[]){
	char *filename;
	FILE *fp;
	int fileSize, fileBytes;
	unsigned int *vector;

	int *map = NULL;
	char *match = NULL;

	int op;
	int i = 0;
	char c = NULL;

	// coleta de dados pelo teclado (nome do arquivo e operação)
	filename = readString();
	scanf("%d", &op);

	// leitura e alocação dos dados do arquivo
	fp = fopen(filename, "r");
	fileBytes = getFileSize(fp);
	vector = (unsigned int *) malloc(fileBytes);
	fileSize = fileBytes / sizeof(unsigned int);
	fread(vector, sizeof(unsigned int), fileSize, fp);

	// (des)inversão dos dados do vetor
	inverseVector(vector, fileSize);

	switch (op){
		case 1: // Mapeamento de Dígitos
			c = *(filename);
			op = atoi(&c);

			map = digitMapping(vector, fileSize, op);
			for (i = 0; i < fileSize; i++){
				printf("%d", *(map+i));
			}
			printf("\n");

			free(map);
			break;
		case 2: // Descriptografia
			shiftDecrypt(vector, fileSize);
			printMessage(vector, fileBytes);
			break;
		case 3: // Contagem de Ocorrências
			shiftDecrypt(vector, fileSize);
			scanf("%c", &c); // limpar o buffer do teclado do último scanf
			match = readString();

			printf("%d\n", search(vector, fileBytes, match));
			free(match);
			break;
	}

	free(vector);
	free(filename);
	fclose(fp);
	return 0;
}