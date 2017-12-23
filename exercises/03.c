#include <stdio.h>
#include <math.h>

int main(int argc, char* argv[]){

    float a;
    scanf("%f", &a);

    printf("%.0f\n", floor(a)); // parte inteira
    printf("%.4f\n", a - floor(a)); // parte decimal
    if (a - floor(a) < 0.5) { // se parte decimal é menor que meio
        printf("%.0f\n", floor(a)); // arredonda pra baixo
    } else {
        printf("%.0f\n", ceil(a)); // arredonda pra cima
    }

}
