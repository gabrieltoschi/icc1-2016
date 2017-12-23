#include <stdio.h>
#include <math.h>

int main (int argc, char* argv[]){

    double a, b, c;
    scanf("%lf%lf%lf", &a, &b, &c);

    double delta, x1, x2;
    delta = b*b - 4*a*c;

    if (delta > 0){
        x1 = (-b + sqrt(delta))/(2*a);
        x2 = (-b - sqrt(delta))/(2*a);
        printf("REAIS\nR1 %lf\nR2 %lf\n", x1, x2);
    }

    if (delta == 0){
        x1 = (-b)/(2*a);
        printf("DUPLA\nRD %lf\n", x1);
    }

    if (delta < 0){
        x1 = (-b)/(2*a);
        x2 = sqrt(-delta)/(2*a);
        printf("COMPLEXAS\nR %lf\nI %lf\n", x1, x2);
    }

    return 0;
}
