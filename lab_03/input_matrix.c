#include "input_matrix.h"

int input_matrix(int *n, int *m, int **A, int **JA, int **IA, int *len_i, int *ct)
{
    int num, i, j;
    int count = 0, len = 0;
    char c;
    printf("Введите количество строк (n):\n");
    if (scanf("%d", n) != 1)
        return ERR_IO;
    if (*n <= 0)
        return ERR_RANGE;
    printf("Введите количество столбцов (m):\n");
    if (scanf("%d", m) != 1)
        return ERR_IO;
    if (*m <= 0)
        return ERR_RANGE;


    (*A) = malloc(sizeof(int) * (*n) * (*m));
    if (A == NULL)
        return ERR_MEM;
    (*JA) = malloc(sizeof(int) * (*n) * (*m));
    if (JA == NULL)
        return ERR_MEM;
    (*IA) = malloc(sizeof(int) * (*n) * (*m));
    if (IA == NULL)
        return ERR_MEM;
    int *tmp_val = calloc((*n) * (*m), sizeof(int));
    if (tmp_val == NULL)
        return ERR_MEM;
    int *tmp_j = calloc((*n) * (*m), sizeof(int));
    if (tmp_j == NULL)
        return ERR_MEM;

    printf("Введите значение и его координаты:\n");
    while (scanf("%d %d %d", &num, &i, &j) == 3)
    {
        if (i >= *n || j >= *m)
            printf("Число за пределами матрицы. Введите другие координаты.\n");
        else
        {
            (*A)[count] = num;
            (*JA)[count] = j;
            tmp_val[i * (*m) + j] = num;
            count++;
        }
        printf("Введите значение и его координаты:\n");
    }
    while ((c = getchar()) != '\n' && c != EOF);
    
    if (count == 0)
    {
        printf("Нет данных.\n");
        return ERR_RANGE;
    }
    count = 0;
    int tmp = -1;
    for (size_t i = 0; i < *n; i++)
    {
        for (size_t j = 0; j < *m; j++)
        {
            num = tmp_val[i * *m + j];
            if (i != tmp)
            {
                (*IA)[len] = count;
                len++;
                tmp = i;
            }
            if (num != 0)
                count++;
        }
    }
    (*len_i) = len;
    (*ct) = count;
    free(tmp_j);
    free(tmp_val);
    return OK;
}

int full_matrix(int **a, int **ia, int **ja, int *n, int *m)
{
    int num, i, j, count = 0, rc  = OK;
    char c;
    printf("Введите количество строк (n):\n");
    if (scanf("%d", n) != 1)
        return ERR_IO;
    if (*n <= 0)
        return ERR_RANGE;
    printf("Введите количество столбцов (m):\n");
    if (scanf("%d", m) != 1)
        return ERR_IO;
    if (*m <= 0)
        return ERR_RANGE;

    (*a) = calloc((*n) * (*m), sizeof(int));
    if (a == NULL)
        return ERR_MEM;
    (*ia) = calloc((*n) * (*m), sizeof(int));
    if (ia == NULL)
        return ERR_MEM;
    (*ja) = calloc((*n) * (*m), sizeof(int));
    if (ja == NULL)
        return ERR_MEM;

    for (size_t i = 0; i < *n; i++)
        for (size_t j = 0; j < *m; j++)
        {
            (*ia)[i * (*m) + j] = i;
            (*ja)[i * (*m) + j] = j;
        }
            
    printf("Введите значение и его координаты:\n");
    while (rc == OK)
    {
        if (scanf("%d %d %d", &num, &i, &j) != 3)
            rc = ERR_IO;
        if (i >= *n || j >= *m)
            printf("Число за пределами матрицы. Введите другие координаты.\n");
        else
        {
            (*a)[i * (*m) + j] = num;
            count++;
        }
        printf("Введите значение и его координаты:\n");
    }
    while ((c = getchar()) != '\n' && c != EOF);
    if (count == 0)
    {
        printf("Нет данных.\n");
        return ERR_RANGE;
    }
    return OK;
}

int input_vector(int **vec, int *n)
{
    int total_count, non_zero_count;

    printf("Введите общее количество элементов в векторе: ");
    if (scanf("%d", &total_count) != 1)
        return ERR_IO;

    if (total_count <= 0)
        return ERR_RANGE;

    printf("Введите количество ненулевых элементов в векторе: ");
    if (scanf("%d", &non_zero_count) != 1)
        return ERR_IO;

    if (non_zero_count <= 0 || non_zero_count > total_count)
        return ERR_RANGE;

    *n = total_count;
    (*vec) = calloc(*n, sizeof(int));
    if ((*vec) == NULL)
        return ERR_MEM;

    printf("Введите ненулевые элементы вектора:\n");
    for (int k = 0; k < non_zero_count; k++) {
        int num;
        if (scanf("%d", &num) != 1)
            return ERR_IO;
        (*vec)[k] = num;
    }

    return OK;
}
