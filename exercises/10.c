#include <stdio.h>
#include <math.h>

int main (int argc, char* argv[]){

    double a, b;
    scanf("%lf%lf", &a, &b);
    printf("%.4lf", pow(a, b));

    return 0;
}
