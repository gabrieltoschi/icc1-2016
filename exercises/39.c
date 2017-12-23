#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void search(char *v, char *m){
	int size = strlen(v);
	int matchsize = strlen(m);
	int match;
	int i, j;

	for (i = 0; i < size-matchsize+1; i++){
		match = 0;
		for (j = 0; j < matchsize; j++){
			if (*(v+i+j) == *(m+j)){
				match++;
			} else {
				break;
			}
		}

		if (match == matchsize){
			printf("SIM\n");
			return;
		}
	}

	printf("NAO\n");
	return;
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

	char *n1 = readString();
	char *n2 = readString();

	long int num1 = atoi(n1);
	long int num2 = atoi(n2);

	if (num1 > num2){
		printf("%ld %ld ", num2, num1);
		search(n1, n2);
	} else {
		printf("%ld %ld ", num1, num2);
		search(n2, n1);
	}

	free(n1);
	free(n2);
	return 0;
}