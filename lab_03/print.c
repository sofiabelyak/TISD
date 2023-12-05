#include "print.h"
void print_matrix_to_vector(int *A, int n)
{
    printf("\nИтоговая матрица:\n");
    for (size_t i = 0; i < n; i++)
    {
        if (A[i] != 0)
            printf("%d\n", A[i]);
    }
    printf("\n");
}

void print_matrix(int *A, int n, int m)
{
    printf("\nИтоговая матрица:\n");
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++) 
            printf("%d ", A[i * m + j]);
        printf("\n");
    }
}