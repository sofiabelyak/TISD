#include "read_matrix.h"
int read_full_matrix_from_file(FILE *f, int **a, int **ia, int **ja, int *n, int *m)
{
    if (fscanf(f, "%d %d", n, m) != 2)
        return ERR_IO;

    int num;
    (*a) = malloc((*n) * (*m) * sizeof(int));
    if (a == NULL)
        return ERR_MEM;
    (*ia) = malloc((*n) * (*m) * sizeof(int));
    if (ia == NULL)
        return ERR_MEM;
    (*ja) = malloc((*n) * (*m) * sizeof(int));
    if (ja == NULL)
        return ERR_MEM;
    for (size_t i = 0; i < *n; i++)
    {
        for (size_t j = 0; j < *m; j++)
        {
            if (fscanf(f, "%d", &num) != 1)
                return ERR_IO;
            (*a)[i * (*m) + j] = num;
            (*ia)[i * (*m) + j] = i;
            (*ja)[i * (*m) + j] = j;
        }
    }
    return OK;
}

int read_matrix_from_file(FILE *f, int **a, int **ia, int **ja, int *n, int *m, int *len_i, int *ct)
{
    if (fscanf(f, "%d %d", n, m) != 2)
        return ERR_IO;

    int num, count = 0, len = 0;
    (*a) = calloc((*n) * (*m), sizeof(int));
    if (a == NULL)
        return ERR_MEM;
    (*ia) = calloc((*n) * (*m), sizeof(int));
    if (ia == NULL)
        return ERR_MEM;
    (*ja) = calloc((*n) * (*m), sizeof(int));
    if (ja == NULL)
        return ERR_MEM;

    int tmp = -1;
    for (size_t i = 0; i < *n; i++)
    {
        for (size_t j = 0; j < *m; j++)
        {
            if (fscanf(f, "%d", &num) != 1)
                return ERR_IO;
            if (i != tmp)
            {
                (*ia)[len] = count;
                len++;
                tmp = i;
            }
            if (num != 0)
            {
                (*a)[count] = num;
                (*ja)[count] = j;

                count++;
            }
        }
    }
    (*ia)[len] = count;
    len++;
    (*len_i) = len;
    (*ct) = count;
    return OK;
}