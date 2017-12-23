#include <stdlib.h>
#include <stdio.h>

typedef struct {
	long long cpf;
	char *name;
	int age;
} person;

char *readString(FILE *stream){
	char *str = NULL;
	char c;
	int ct = 0;

	do {
		c = fgetc(stream);
		str = (char *) realloc(str, sizeof(char)*(ct+1));
		str[ct++] = c;
	} while (c != '\n' && c != EOF);

	str[--ct] = '\0';
	return str;
}

long long readCPF(char *read){
	char *aux;
	long long cpf;
	int i, j = 0;

	aux = (char *) malloc (sizeof(char)*12);
	aux[11] = '\0';
	for (i = 0; i < 15; i++){
		if (read[i] != '.' && read[i] != '-') aux[j++] = read[i];
	}
	cpf = atoll(aux);
	free(aux);
	return cpf;
}

person *readFile(FILE *stream, int *ct){
	person *people = NULL;
	int toRead = 0, n = 0;
	char *read;

	while(!feof(stream)){
		read = readString(stream);
		if (!feof(stream)){
			switch (toRead){
				case 0:
					people = (person *) realloc(people, sizeof(person)*(n+1));
					toRead++;
				case 1:
					people[n].cpf = readCPF(read);
					free(read);
					toRead++;
					break;
				case 2:
					people[n].name = read;
					toRead++;
					break;
				case 3:
					people[n++].age = atoi(read);
					free(read);
					toRead = 0;
					break;
			}
		} else free(read);
	}

	*ct = n;
	return people;
}

void sortByCPF(person *p, int n){
	int i, j;
	person aux;

	for (i = 1; i < n; i++){
		for (j = 0; j < n-i; j++){
			if (p[j].cpf > p[j+1].cpf){
				aux = p[j+1];
				p[j+1] = p[j];
				p[j] = aux;
			}
		}
	}
}

void printCPF(long long cpf){
	char *received = malloc(sizeof(char)*12);
	char *formatted = malloc(sizeof(char)*15);
	sprintf(received, "%lli", cpf);
	int f, r = 0;

	for (f = 0; f < 15; f++){
		if (f == 3 || f == 7) formatted[f] = '.';
		else if (f == 11) formatted[f] = '-';
		else formatted[f] = received[r++];
	}

	printf("%s\n", formatted);
	free(formatted);
	free(received);
}

void printPerson(person p){
	printCPF(p.cpf);
	printf("%s\n", p.name);
	printf("%d\n", p.age);
	free(p.name);
}

void compareAndPrint(person *f1, int n1, person *f2, int n2){
	int i;
	int ct1 = 0, ct2 = 0;

	for (i = 0; i < n1+n2; i++){
		if (ct1 >= n1){ // não há mais pessoas no arquivo 1
			printPerson(f2[ct2++]);
		} else {
			if (ct2 >= n2){ // não há mais pessoas no arquivo 2
				printPerson(f1[ct1++]);
			} else {
				if (f1[ct1].cpf < f2[ct2].cpf){ // cpf do arquivo 1 é menor
					printPerson(f1[ct1++]);
				} else { // cpf do arquivo 2 é menor
					printPerson(f2[ct2++]);
				}
			}
		}
	}
}

int main(int argc, char *argv[]){

	char *filen1, *filen2;
	FILE *fp1, *fp2;
	char *read;
	person *people1 = NULL;
	person *people2 = NULL;
	int toRead = 0, n1, n2;

	filen1 = readString(stdin);
	filen2 = readString(stdin);

	fp1 = fopen(filen1, "r");
	fp2 = fopen(filen2, "r");

	people1 = readFile(fp1, &n1);
	people2 = readFile(fp2, &n2);

	sortByCPF(people1, n1);
	sortByCPF(people2, n2);

	compareAndPrint(people1, n1, people2, n2);

	fclose(fp1);
	fclose(fp2);
	free(filen1);
	free(filen2);

	return 0;
}