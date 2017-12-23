#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
* Nota: correspondente letra-numero e' um número natural relacionado a cada letra do alfabeto,
* considerando A = 0, B = 1, C = 2, ..., Y = 24, Z = 25
*/

void caesar(char* message, int key){
	int i;  // i: contador para loop

	for (i = 0; i < strlen(message); i++){ // percorre toda a mensagem
		if (message[i] >= 65 && message[i] <= 90){ // verifica se o caractere e' uma letra
												   // maiúscula para ser alterada
			message[i] -= 65; // encontra o correspondente letra-numero
			
			// soma-se a letra com a chave e encontra o modulo deste numero com 26 (total de
			// letras); se ele for menor que 26, tem-se o mesmo numero
			// soma-se posteriormente a 65 para voltar a um valor correspondente da tabela ASCII
			message[i] = ((message[i] + key) % 26) + 65;
		}
	}
}

void vigenere(char* message, char* key){
	int i;            // i: contador para loop
	int keycount = 0; // keycount: contador para percorrer a chave

	for (i = 0; i < strlen(message); i++){
		if(message[i] >= 65 && message[i] <= 90){
			message[i] -= 65;

			// encontra-se a posição na chave correspondente a posicao da palavra, mesmo
			// que a chave deva ser repetida. depois, aplica-se uma cifra de Cesar considerando
			// o correspondente letra-numero do caracter desta posicao na chave.
			// por fim, retorna este valor a um correspondente ASCII
			message[i] = (((message[i] + (key[keycount++ % strlen(key)] - 65)) % 26)) + 65;
		}
	}
}

char *readLine(int sz){
	char *word = NULL; // word: ponteiro para armazenar uma palavra
	char c;        // c: variavel para guardar cada caractere da palavra
	int ct;        // ct: contador de caracteres da palavra

	scanf("%c", &c); // como readLine não e' a primeira leitura feita do programa, um primeiro
	       	         // scanf deve ser feito para ler a tecla Enter, dada para terminar a
					 // leitura anterior

	word = (char *) malloc((sizeof(char))*(sz+1)); // aloca memoria heap

	for (ct = 0; ct < sz; ct++){
		scanf("%c", &c); // le caractere por caractere
		word[ct] = c; // coloca o caractere na heap recem-armazenada
	} 
	word[sz] = '\0';  // fim de string = \0
	return word;
}

int main(int argc, char* argv[]){

	int msize;     // msize: tamanho (em caracteres) da mensagem
	scanf("%d", &msize);  

	char* message; // message: aponta para onde esta armazenada a mensagem na Heap
	message = readLine(msize); 

	int op; // op: mostra a criptografia a ser feita
	scanf("%d", &op);

	int keynum; // keynum: chave de deslocamento da cifra de Cesar/tamanho (em caracteres) da
                //                                                 chave da cifra de Vigenere
	char *vkey; // vkey: chave de deslocamento da cifra de Vigenere

	switch (op){ // condicao para escolha de criptografia
		case 1: // 1 -> cifra de Cesar
			scanf("%d", &keynum); 
			caesar(message, keynum); 
			break;
		case 2: // 2 -> cifra de Vigenere
			
			scanf("%d", &keynum); 
			vkey = readLine(keynum);
			vigenere(message, vkey);

			free(vkey); // liberacao de memoria heap
			break;
	}

	printf("%s", message);

	free(message); // liberacao de memoria heap
	return 0;
}