#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

int main() {
    int num, i;
    printf("Enter the number of steps: ");
    scanf("%d", &num);

    clock_t st, et;
    st = clock();

    double step = 1.0 / (double)num;
    double pi = 0.0;

    #pragma omp parallel for reduction(+:pi)
    for (i = 0; i < num; i++) {
        double x = (i + 0.5) * step;
        pi += 4.0 / (1.0 + x * x);
    }

    pi *= step;
    et = clock();

    printf("Time Taken: %lf seconds\n", (double)(et - st) / CLOCKS_PER_SEC);
    printf("Value of Pi = %.16lf\n", pi);

    return 0;
}
