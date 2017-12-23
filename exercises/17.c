#include <stdlib.h>
#include <stdio.h>

#define TRUE 1
#define FALSE 0

int isUpper(char c){
	if (c >= 65 && c <= 90){
		return TRUE;
	} else {
		return FALSE;
	}
}

int main (int argc, char *argv[]){

	char *cadeia = NULL;
	char c;
	int ct = 0;
	int i;

	do {
		scanf("%c", &c);
		cadeia = (char *) realloc(cadeia, sizeof(char)*(ct+1));
		cadeia[ct++] = c;
	} while (c != '\n');
	cadeia[--ct] = '\n';

	for (i = 0; i < ct; i++){
		if (isUpper(cadeia[i])){
			printf("%c", cadeia[i]+32);
		} else {
			printf("%c", cadeia[i]);
		}
	}

	printf("\n");

	free(cadeia);
	return 0;
}