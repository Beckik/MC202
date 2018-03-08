#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    double** matrix;
    double amount = 0, mean = 0, pop = 0;
    int number;
    int i, j;

    scanf("%d", &number);

    matrix = malloc(number*sizeof(double*));
    for (i = 0; i < number; ++i) {
        matrix[i] = malloc((i+1)*sizeof(double));
    }

    for (i = 0; i < number; ++i) {
        for (j = 0; j < i+1; ++j) {
            scanf("%lf", &matrix[i][j]);
        }
    }

    for (i = 0; i < number; ++i) {
        for (j = 0; j < i+1; ++j) {
            mean = matrix[i][j] + mean;
        }
    }

    amount = (((number*number)+number)/2);

    mean = mean/amount;

    for (i = 0; i < number; ++i) {
        double aux = 0;
        for (j = 0; j < i+1; ++j) {
            aux = (matrix[i][j] - mean);
            aux = aux* aux;
            pop = aux + pop;
        }
    }

    pop = pop/amount;

    pop = sqrt(pop);

    for (i = 0; i < number; ++i) {
        for (j = 0; j < i+1; ++j) {
            matrix[i][j] = (matrix[i][j]-mean)/pop;
        }
    }


    for (i = 0; i < number; ++i) {
        for (j = 0; j < i+1; ++j) {
            printf("%.12lf ", matrix[i][j]);
        }
        printf("\n");
    }

    printf("\n");

    printf("%.12lf %.12lf \n", mean, pop);

    free(matrix);

    return 0;
}