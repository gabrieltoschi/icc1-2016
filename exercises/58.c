#include <stdlib.h>
#include <stdio.h>

long getFileSize(FILE *f){
	/** retorna o tamanho (em bytes) de um arquivo **/
	long currentSize, fileSize;

	// currentSize guarda a posição atual do arquivo para colocá-lo
	// novamente nessa posição após o uso da função
	currentSize = ftell(f);

	// leva o cursor até o final do arquivo e usa ftell para saber
	// quantos bytes existem entre o inicio e o final
	fseek(f, 0, SEEK_END);
	fileSize = ftell(f);

	// leva o arquivo novamente ao local original
	fseek(f, currentSize, SEEK_SET);

	return fileSize;
}

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

int main(int argc, char *argv[])
{
	char *filename;
	FILE *fp;

	filename = readString(stdin);
	fp = fopen(filename, "r");

	printf("%li\n", getFileSize(fp));

	free(filename);
	fclose(fp);
	return 0;
}