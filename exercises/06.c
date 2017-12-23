#include <stdio.h>
#include <math.h>
#include <stdbool.h>

int main (int argc, char* argv[]){

    double x1, y1, x2, y2;
    double res = 0;
    bool first = false;
    int n, i;

    scanf("%d", &n);

    for (i = 0; i < n; i++){
    if (!first){
        scanf("%lf%lf", &x1, &y1);
        first = true;
    } else {
        x2 = x1;
        y2 = y1;
        scanf("%lf%lf", &x1, &y1);

        res = res + sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
    }

    }

    printf("%.4lf\n", res);
    return 0;
}
