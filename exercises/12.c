#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]){

	char *palavra = NULL;
	char c;
	int i;
	int tam = 0;
	do
	{
		scanf("%c", &c);
		palavra = (char *) realloc(palavra, sizeof(char)*(tam+1));
		palavra[tam++] = c;
	} while (c != '\n');
	palavra[--tam] = '\0';

	for (i = 0; i < tam/2; i++){
    	if (palavra[i] != palavra[tam-i-1]){
    		printf("NAO\n");
    		return 0;
    	}

    }
    printf("SIM\n");
    free(palavra);
    return 0;
}