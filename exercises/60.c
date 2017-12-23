#include <stdlib.h>
#include <stdio.h>

int *readCharMap(int *numread){
	int *charmap = (int *) calloc(256, sizeof(int));
	char c;
	int read = 0;

	do {
		scanf("%c", &c);
		if (c != '\n'){
			charmap[(int) c]++; 
			read++;
		}
	} while (c != 'x');

	*numread = read;
	return charmap;
}

int main(int argc, char *argv[]){

	int i, read, curascii = 0;
	int *charmap = readCharMap(&read);
	char *alloc = (char *) malloc(sizeof(char)*4);
	int *print = (int *) alloc;

	for (i = 0; i < read; i++){
		while (charmap[curascii] == 0) curascii++;

		alloc[i%4] = (char) curascii;
		charmap[curascii]--;

		if (i%4 == 3) printf("%d\n", print[0]);
	}

	free(charmap);
	free(alloc);

	return 0;
}