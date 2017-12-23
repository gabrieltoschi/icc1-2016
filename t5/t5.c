#include <stdlib.h>
#include <stdio.h>

typedef struct Node Node;
typedef struct Deque Deque;

/* Estrutura que armazena um elemento do Deque. */
struct Node {
	Node *prev;
	Node *next;
	char elem;
};

/* Estrutura que armazena o Deque completo (referência para os Nodes encadeados). */
struct Deque {
	Node *front;
	Node *back;
};

/* Aloca um Deque vazio na Heap. */
Deque *create(){
	Deque *new = (Deque *) malloc(sizeof(Deque));
	new->front = NULL;
	new->back = NULL;

	return new;
}

/* Retorna 1 caso o Deque esteja vazio e 0 caso contrário. */
int empty(Deque *deque){
	if (deque->front == NULL && deque->back == NULL) return 1;
		else return 0;
}

/* Remove todos os elementos do Deque. */
void clear(Deque *deque){
	Node *nextToClear = deque->back;
	Node *cleaning;

	// desaloca cada nó, do começo para o fim, até encontrar NULL como próximo
	while (nextToClear != NULL){
		cleaning = nextToClear;
		nextToClear = cleaning->next;
		free(cleaning);
	}

	deque->front = NULL;
	deque->back = NULL;
}

/* Remove todos os elementos e desaloca o Deque. */
void destroy(Deque *deque){
	if (!empty(deque)) clear(deque);
	free(deque);
}

/* Insere um elemento na frente (na cabeça) do Deque. */
void push_front(Deque *deque, char new){
	Node *newNode = (Node *) malloc(sizeof(Node));
	newNode->elem = new;
	newNode->next = NULL;

	if (empty(deque)){
		// se o deque estiver vazio, o novo nó é tanto o primeiro quanto o último
		newNode->prev = NULL;
		deque->front = newNode;
		deque->back = newNode;
	} else {
		newNode->prev = deque->front;
		deque->front->next = newNode;
		deque->front = newNode;
	}
}

/* Insere um elemento atrás (na cauda) do Deque. */
void push_back(Deque *deque, char new){
	Node *newNode = (Node *) malloc(sizeof(Node));
	newNode->elem = new;
	newNode->prev = NULL;

	if (empty(deque)){
		// se o deque estiver vazio, o novo nó é tanto o primeiro quanto o último
		newNode->next = NULL;
		deque->front = newNode;
		deque->back = newNode;
	} else {
		newNode->next = deque->back;
		deque->back->prev = newNode;
		deque->back = newNode;
	}
}

/* Retorna o elemento armazenado na frente do Deque. */
char front(Deque *deque){
	// se o deque estiver vazio (aka a cabeça conter NULL), retorna '\0'
	return deque->front == NULL ? '\0' : deque->front->elem;
}

/* Retorna o elemento armazenado atrás do Deque. */
char back(Deque *deque){
	// se o deque estiver vazio (aka a cauda conter NULL), retorna '\0'
	return deque->back  == NULL ? '\0' : deque->back->elem;
}

/* Retorna a quantidade de elementos do Deque. */
int size(Deque *deque){
	Node *counting = deque->back;
	int counter = 0;

	while (counting != NULL){
		counting = counting->next;
		counter++;
	}

	return counter;
}

/* Remove o elemento da frente do Deque. */
void pop_front(Deque *deque){
	// se o deque tiver apenas um elemento, use a função clear
	if (size(deque) == 1) clear(deque);
	else if (!empty(deque)){
		Node *newFront = deque->front->prev;
		newFront->next = NULL;
		free(deque->front);
		deque->front = newFront;
	}
}

/* Remove o elemento de trás do Deque. */
void pop_back(Deque *deque){
	// se o deque tiver apenas um elemento, use a função clear
	if (size(deque) == 1) clear(deque);
	else if (!empty(deque)){
		Node *newBack = deque->back->next;
		newBack->prev = NULL;
		free(deque->back);
		deque->back = newBack;
	}
}

/* Imprime um node do Deque e chama a impressão do próximo recursivamente. */
void printNode(Node *node){
	printf("%c", node->elem);

	if (node->next != NULL) printNode(node->next);
}

/* Imprime todos os elementos armazenados no Deque. */
void print(Deque *deque){
	if (!empty(deque)) {
		printNode(deque->back);
		printf("\n");
	}
}

/* Lê uma string de um stream de dados e armazena-a em um Deque, caractere a caractere. */
Deque *readStringDeque(FILE *stream, char delim){
	Deque *string = create();
	char read;

	do {
		read = fgetc(stream);
		push_front(string, read);
	} while (read != delim);

	pop_front(string);
	return string;
}

/* Seção 4.1: The Last Word */
void lastWord(FILE *stream){
	Deque *last = create();
	char read = fgetc(stream);

	while (read != '\n'){ // lê cada caractere da string inicial

		// se a nova letra for maior que a última letra da string que está sendo formada, 
		// coloque-a na cauda do deque
		if (read >= back(last)) push_back(last, read);
			// se não, coloque na cabeça do deque
			else push_front(last, read);
		read = fgetc(stream);
	}

	print(last);
	destroy(last);
}

/* Seção 4.2: Strings */
int validationByExtremes(Node *base, Node *back, Node *front){
	// CONDIÇÃO: o elemento final da string base é igual à cabeça 
	// e à cauda da string testada
	if (base->elem == back->elem && base->elem == front->elem){
		// CONDIÇÃO DE PARADA: se ambos os ponteiros vindos da cabeça e
		// da cauda sejam iguais, a palavra É VÁLIDA
		if (back == front) return 1;
		// PASSO RECURSIVO: divida a árvore recursiva, tirando, da string
		// testada, a letra da cabeça ou da cauda
		else return validationByExtremes(base->prev, back->next, front) |
					validationByExtremes(base->prev, back, front->prev);
	// CONDIÇÃO: o elemento final da string base é igual à cauda
	// da string testada
	} else if (base->elem == back->elem)
		// PASSO RECURSIVO: tire, da string testada, a letra da cauda
		return validationByExtremes(base->prev, back->next, front);
	// CONDIÇÃO: o elemento final da string base é igual à cabeça
	// da string testada
	else if (base->elem == front->elem)
		// PASSO RECURSIVO: tire, da string testada, a letra da cabeça
		return validationByExtremes(base->prev, back, front->prev);
	// CONDIÇÃO DE PARADA: o elemento final da string base não é igual
	// nem à cabeça nem à cauda da string testada, a palavra NÃO É VÁLIDA
	else return 0;
}

void stringValidation(FILE *stream){
	Deque *baseString = readStringDeque(stream, '\n');
	Deque *validString = readStringDeque(stream, '\n');

	// busca pela validação da palavra que foi entrada no programa
	if (validationByExtremes(baseString->front, validString->back, validString->front))
		printf("S\n");
	else printf("N\n");

	destroy(baseString);
	destroy(validString);
}

int main(int argc, char *argv[]){
	
	int op;
	scanf("%d\n", &op);

	switch (op){
		case 1:
			lastWord(stdin);
			break;
		case 2:
			stringValidation(stdin);
			break;
	}
	return 0;
}
