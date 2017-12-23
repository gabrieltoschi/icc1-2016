#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *readLine(){
	char *word = NULL;
	char c;
	int i;
	int sz = 0;

	do
	{
		scanf("%c", &c);
		word = (char *) realloc(word, sizeof(char)*(sz+1));
		word[sz++] = c;
	} while (c != '\n');
	word[--sz] = '\0';

	return word;
}

int main(int argc, char *argv[]){

	char *palavra = NULL;
	int i;
	int tam;

	palavra = readLine();
	tam = strlen(palavra);

	for (i = 0; i < tam/2; i++){
    	if (palavra[i] != palavra[tam-i-1]){
    		printf("NAO\n");
    		free(palavra);
    		return 0;
    	}

    }
    printf("SIM\n");
    free(palavra);
    return 0;
}