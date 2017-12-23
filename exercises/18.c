#include <stdlib.h>
#include <stdio.h>

int main (int argc, char *argv[]){

	char *number = NULL;
	char c;
	int i;
	int ct = 0;
	int sum = 0;

	do {
		scanf("%c", &c);
		number = (char *) realloc(number, sizeof(char)*(ct+1));
		number[ct++] = c;
	} while (c != '\n');
	number[--ct] = '\0';

	for (i = 0; i < ct; i++){
		c = number[i];
		sum += atoi(&c);
	}

	printf("%d", sum);

	return 0;
}