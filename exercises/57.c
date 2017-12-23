#include <stdlib.h>
#include <stdio.h>

typedef struct {
	char d;
	char m;
	int y;
} Date;

typedef struct {
	char h;
	char m;
	char s;
} Hour;

typedef struct {
	Date date;
	Hour hour;
	char *desc;
} Entry;

char *readString(){
	char *str = NULL;
	char c;
	int ct = 0;

	do {
		c = fgetc(stdin);
		str = (char *) realloc(str, sizeof(char)*(ct+1));
		str[ct++] = c;
	} while (c != '\n');

	str[--ct] = '\0';
	return str;
}

int readNumericData(){
	char *aux;
	int aux2;

	aux = readString();
	aux2 = atoi(aux);
	free(aux);
	return aux2;
}

int main (int argc, char *argv[]){
	int n, i;
	Entry *agenda;
	char aux;

	scanf("%d", &n);
	aux = fgetc(stdin);
	agenda = (Entry *) malloc(sizeof(Entry)*n);

	for (i = 0; i < n; i++){
		agenda[i].date.d = readNumericData();
		agenda[i].date.m = readNumericData();
		agenda[i].date.y = readNumericData();
		agenda[i].hour.h = readNumericData();
		agenda[i].hour.m = readNumericData();
		agenda[i].hour.s = readNumericData();
		agenda[i].desc = readString();
	}

	for (i = 0; i < n; i++){
		printf("%.2d/%.2d/%.2d - %.2d:%.2d:%.2d\n", 
			agenda[i].date.d, agenda[i].date.m, agenda[i].date.y,
			agenda[i].hour.h, agenda[i].hour.m, agenda[i].hour.s);
		printf("%s\n", agenda[i].desc);
		free(agenda[i].desc);
	}

	free(agenda);

	return 0;
}