#include "multiply_matrix.h"

void multiply_sparse_matrix_to_vector(int *Val, int *Row, int *Col, int *vec, int n, int nv, int **c)
{
    *c = calloc(nv, sizeof(int));

    for (size_t i = 0; i < n; i++) {
        for (size_t j = Row[i]; j < Row[i + 1]; j++)
         {
            (*c)[i] += Val[j] * vec[Col[j]];
        }
    }
}

void multiply_matrix_to_vector(int *A, int *IA, int *JA, int *v, int n, int m, int nv, int **c)
{
    (*c) = calloc(nv, sizeof(int));
    
    for (size_t i = 0; i < n * m; i++)
    {
        if (IA[i] < IA[i + 1]) 
        {
            (*c)[IA[i]] += A[i] * v[JA[i]];
        }
    }
}