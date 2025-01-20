#include <stdio.h>
#include <omp.h>
#include <time.h>

int main() {
    int n;

    printf("Enter size: ");
    scanf("%d", &n);

    int A[n][n], x[n], y[n];

    printf("Enter matrix A:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &A[i][j]);
        }
    }

    printf("Enter vector x:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &x[i]);
        y[i] = 0;
    }

    clock_t start = clock();

    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            y[i] += A[i][j] * x[j];
        }
    }

    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Result y: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", y[i]);
    }
    printf("\n");

    printf("Execution time: %f seconds\n", time_taken);

    return 0;
}
