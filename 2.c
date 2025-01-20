#include <stdio.h>
#include <time.h>
#include <omp.h>

int main() {
    int clothing, gaming, grocery, stationary;
    int total_amount = 0; 

    clock_t start_time, end_time; 

    printf("Enter the amount for clothing: ");
    scanf("%d", &clothing);
    printf("Enter the amount for gaming: ");
    scanf("%d", &gaming);
    printf("Enter the amount for grocery: ");
    scanf("%d", &grocery);
    printf("Enter the amount for stationary: ");
    scanf("%d", &stationary);

    
    start_time = clock(); 

    total_amount = clothing + gaming + grocery + stationary;

    end_time = clock(); 

    printf("Total Amount (Serial): %d\n", total_amount);

    printf("Serial Execution Time: %f seconds\n", 
           (double)(end_time - start_time) / CLOCKS_PER_SEC);

    total_amount = 0;

    start_time = clock(); 

    #pragma omp parallel
    {
        #pragma omp sections
        {
            #pragma omp section
            {
                #pragma omp atomic
                total_amount += clothing;
            }
            #pragma omp section
            {
                #pragma omp atomic
                total_amount += gaming;
            }
            #pragma omp section
            {
                #pragma omp atomic
                total_amount += grocery;
            }
            #pragma omp section
            {
                #pragma omp atomic
                total_amount += stationary;
            }
        }
    }

    end_time = clock(); 

    printf("Total Amount (Parallel): %d\n", total_amount);

    printf("Parallel Execution Time: %f seconds\n", 
           (double)(end_time - start_time) / CLOCKS_PER_SEC);

    return 0;
}
