#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int search(char *str, char c){
	int size = strlen(str);
	int found = 0;
	int i;

	for (i = 0; i < size; i++){
		if (str[i] == c) found++;
	}

	return found;
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

	char *string;
	char c;

	string = readString();
	scanf("%c", &c);

	printf("%d\n", search(string, c));

	free(string);
	return 0;
}