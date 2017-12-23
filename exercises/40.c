#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void printString(char *str){
	int i;
	int sz = strlen(str);

	for (i = 0; i < sz; i++){
		printf("%c\n", *(str+i));
	}
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

int main (int argc, char *argv[]){

	char *str = readString();
	printString(str);
	free(str);

	return 0;
}