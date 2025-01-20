#include <stdio.h>
#include <omp.h>
#include <time.h>
#define NUM_STUDENTS 10

int main() {
    float cpgas[NUM_STUDENTS] = {2.0, 3.9, 3.5, 4.0, 3.7, 3.9, 3.1, 3.6, 3.8, 3.3};
    float max_cgpa;
    
    // Sequential version
    clock_t start = clock();
    max_cgpa = cpgas[0];
    for (int i = 1; i < NUM_STUDENTS; i++) {
        if (cpgas[i] > max_cgpa) {
            max_cgpa = cpgas[i];
        }
    }
    printf("Sequential: Max CGPA = %f\n", max_cgpa);
    printf("Time (seq): %f seconds\n", (double)(clock() - start) / CLOCKS_PER_SEC);

    // Parallel version
    max_cgpa = 0.0;
    start = clock();
    #pragma omp parallel for reduction(max:max_cgpa)
    for (int i = 0; i < NUM_STUDENTS; i++) {
        if (cpgas[i] > max_cgpa) {
            max_cgpa = cpgas[i];
        }
    }
    printf("Parallel: Max CGPA = %f\n", max_cgpa);
    printf("Time (par): %f seconds\n", (double)(clock() - start) / CLOCKS_PER_SEC);
    
    return 0;
}
