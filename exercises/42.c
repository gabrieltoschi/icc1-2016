#include <stdlib.h>
#include <stdio.h>

int checkWin(char **game){
	int x, y;
	char chk1, chk2;

	// checando linhas e colunas
	for (x = 0; x < 3; x++){
		chk1 = 0;
		chk2 = 0;
		for (y = 0; y < 3; y++){
			chk1 += game[x][y];
			chk2 += game[y][x];
		}

		if (chk1 == 3 || chk2 == 3) {
			return 1;
		} else if (chk1 == -3 || chk2 == -3){
			return 0;
		}
	}

	chk1 = 0;
	chk2 = 0;

	// checando diagonais
	for (x = 0; x < 3; x++){
		chk1 += game[x][x];
		chk2 += game[x][2-x];

		if (chk1 == 3 || chk2 == 3) {
			return 1;
		} else if (chk1 == -3 || chk2 == -3){
			return 0;
		}
	}

	return -1;
}

int main (int argc, char *argv[]){

	int i, x, y, win;
	int player = -1;

	char **game = (char **) calloc(3, sizeof(char *));
	for (i = 0; i < 3; i++){
		game[i] = (char *) calloc(3, sizeof(char));
	}

	while (scanf("%d%d", &x, &y) != EOF){
		game[x][y] = player;
		player *= -1;
	}

	win = checkWin(game);
	if (win == -1) printf("empate\n");
		else printf("%d\n", win);

	for (i = 0; i < 3; i++){
		free(game[i]);
	}
	free(game);

	return 0;
}