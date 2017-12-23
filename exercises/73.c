#include <stdlib.h>
#include <stdio.h>

char *readSwappedString (char delim, char swap, char new){
	char *string = NULL;
	int count = 0;
	char c;

	do {
		c = fgetc(stdin);
		string = (char *) realloc(string, sizeof(char)*(count+1));
		string[count++] = c == swap ? new : c;
	} while (c != delim);

	string[--count] = '\0';
	return string;
}

char *jumpNext(char *entry){
	while (*entry != '\0') entry++;
	return entry+1;
}

int main (int argc, char *argv[]){
	char *IPv4, *toConv;
	int i, j, conv, firstIsZero = 0;

	IPv4 = readSwappedString('\n', '.', '\0');
	toConv = IPv4;

	printf(":::::ffff:");

	for (i = 0; i < 2; i++){
		for (j = 0; j < 2; j++){
			conv = atoi(toConv);

			if (j == 0){ // primeiro numero do espaço IPv6
				if (conv == 0) firstIsZero = 1;
				else if (conv <= 15) printf("%01x", conv);
				else printf("%02x", conv);
			} else { // segundo numero
				if (firstIsZero && conv == 0) break;
				else if (firstIsZero && conv <= 15) printf("%01x", conv);
				else printf("%02x", conv);
			}
			toConv = jumpNext(toConv);
		}
		firstIsZero = 0;
		if (i == 0) printf(":");
	}

	free(IPv4);
}