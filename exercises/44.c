#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

void wordUpper(char *word){
	int i;
	for (i = 0; word[i] != '\0'; i++){
		word[i] = toupper(word[i]);
	}
}

char **readWords(int *wordcounter){
	char **words = NULL;
	char c;
	int ct = 0;
	int wct = 0;

	words = (char **) calloc(1, sizeof(char *));

	do {
		scanf("%c", &c);
		if (c == ' ') {
			words[wct][ct] = '\0';
			ct = 0;
			words = (char **) realloc(words, sizeof(char *)*(wct+2));
			words[++wct] = NULL;
		} else {
			words[wct] = (char *) realloc(words[wct], sizeof(char)*(ct+1));
			words[wct][ct++] = c;
		}
	} while (c != '\n');

	words[wct][ct-1] = '\0';
	ct = 0;
	*(wordcounter) = wct+1;
	return words;
}

int main (int argc, char *argv[]){
	char **name;
	int nct, i;

	name = readWords(&nct);
	wordUpper(name[nct-1]);

	printf("%s, ", name[nct-1]);
	free(name[nct-1]);

	for (i = 0; i < nct-2; i++){
		printf("%s ", name[i]);
		free(name[i]);
	} 

	printf("%s\n", name[nct-2]);
	free(name[nct-2]);

	free(name);
	return 0;
}