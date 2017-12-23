#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef enum {
	false,
	true
} bool;

/** ESTRUTURAS DE OBJETO **/
typedef struct {
	double x1;
	double x2; 
	double y1;
	double y2;
} Rect;

typedef struct {
	double x;
	double y;
	double radius;
} Circle;

typedef struct {
	double x;
	double y;
	double side;
} Square;

/** FUNÇÕES PARA LEITURA DE OBJETO **/
Rect *readRects(int n){
	int i;
	Rect *rects = (Rect *) malloc(sizeof(Rect)*n);

	for (i = 0; i < n; i++){
		scanf("%lf%lf%lf%lf", &rects[i].x1, &rects[i].y1,
							  &rects[i].x2, &rects[i].y2);
	}

	return rects;
}

Circle *readCircles(int n){
	int i;
	Circle *circles = (Circle *) malloc(sizeof(Circle)*n);

	for (i = 0; i < n; i++){
		scanf("%lf%lf%lf", &circles[i].x, &circles[i].y, &circles[i].radius);
	}

	return circles;
}

Square *readSquares(int n){
	int i;
	Square *squares = (Square *) malloc(sizeof(Square)*n);

	for (i = 0; i < n; i++){
		scanf("%lf%lf%lf", &squares[i].x, &squares[i].y, &squares[i].side);
	}

	return squares;
}

/** COLISÃO DE RETÂNGULOS **/
bool pointRectCollider(Rect b, int xc, int yc){
	if (xc >= b.x1 && xc <= b.x2 && yc >= b.y1 && yc <= b.y2) return true;
		else return false;
}
  
bool rectCollider(Rect *a, Rect *b){
	if (pointRectCollider(*a, b->x1, b->y1) ||
		pointRectCollider(*a, b->x1, b->y2) ||
		pointRectCollider(*a, b->x2, b->y1) ||
		pointRectCollider(*a, b->x2, b->y2)) return true;
	else return false;
}

/** COLISÃO DE QUADRADOS **/
bool pointSquareCollider(Square b, int xc, int yc){
	double inc = (b.side)/2;
	if (xc >= (b.x)-inc && xc <= (b.x)+inc
	 							&& yc >= (b.y)-inc && yc <= (b.y)+inc) return true;
		else return false;
}

bool squareCollider(Square *a, Square *b){
	double inc = (b->side) / 2;
	if (a->x == b->x && a->y == b->y) return true;
	else if (pointSquareCollider(*a, (b->x)-inc, (b->x)-inc) ||
			 pointSquareCollider(*a, (b->x)+inc, (b->x)-inc) ||
		 	 pointSquareCollider(*a, (b->x)-inc, (b->x)+inc) ||
		 	 pointSquareCollider(*a, (b->x)+inc, (b->x)+inc)) return true;
	else return false;
}

/** COLISÃO DE CÍRCULOS **/
double euclidianDistance(double x1, double y1, double x2, double y2){
	double potX = pow(x2 - x1, 2);
	double potY = pow(y2 - y1, 2);
	double aux = potX + potY;
	return sqrt(aux);
}

bool circleCollider(Circle *a, Circle *b){
	if (euclidianDistance(a->x, a->y, b->x, b->y) <= (a->radius + b->radius))
		return true;
	else return false;
}

int main (int argc, char*argv[]){
	char op;
	int objCt, i, j, pointerInc;
	bool (*collider)(void *, void *);
	void *objects;
	bool collided = false;
	
	scanf("%c\n%d", &op, &objCt);

	switch (op){
		case 'r':
			collider = (bool (*)(void *, void *)) &rectCollider;
			objects = (void *) readRects(objCt);
			pointerInc = sizeof(Rect);
			break;
		case 'c':
			collider = (bool (*)(void *, void *)) &circleCollider;
			objects = (void *) readCircles(objCt);
			pointerInc = sizeof(Circle);
			break;
		case 'q':
			collider = (bool (*)(void *, void *)) &squareCollider;
			objects = (void *) readSquares(objCt);
			pointerInc = sizeof(Square);
			break;
	}

	for (i = 0; i < objCt && !collided; i++){
		for (j = i; j < objCt && !collided; j++){
			if (i != j)	collided = collider((void *) objects+(i*pointerInc), 
											(void *) objects+(j*pointerInc));
		}
	}

	if (collided) printf("SIM\n");
		else printf("NAO\n");

	free(objects);
	return 0;
}