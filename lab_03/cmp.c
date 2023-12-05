#define _POSIX_C_SOURCE 199309L
#include "cmp.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

// Функция для генерации случайного числа в диапазоне [0, 100]
int random_percentage() 
{
    return rand() % 101;
}

// Функция для заполнения разреженной матрицы случайными значениями
void fill_sparse_matrix(int *A, int *IA, int *JA, int n, int m, int fill_percentage) {
    int nonzero_count = 0;

    for (int i = 0; i < n; i++) {
        IA[i] = nonzero_count;
        for (int j = 0; j < m; j++) {
            if (random_percentage() <= fill_percentage) {
                A[nonzero_count] = random_percentage();
                JA[nonzero_count] = j;
                nonzero_count++;
            }
        }
    }
    IA[n] = nonzero_count;
}


// Функция для заполнения стандартной матрицы случайными значениями
void fill_standard_matrix(int *A, int n, int m, int fill_percentage) {
    int nonzero_count = (fill_percentage * n * m) / 100;

    for (int i = 0; i < n * m; i++) {
        A[i] = 0;
    }

    for (int i = 0; i < nonzero_count; i++) {
        int random_row = rand() % n;
        int random_col = rand() % m;
        int random_index = random_row * m + random_col;
        A[random_index] = random_percentage();
    }
}


// Функция для сравнения времени выполнения операций
void compare_matrix_operations() {
    int n, m;
    printf("Введите количество строк матрицы: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Некорректный ввод для количества строк.\n");
        return;
    }

    printf("Введите количество столбцов матрицы: ");
    if (scanf("%d", &m) != 1 || m <= 0) {
        printf("Некорректный ввод для количества столбцов.\n");
        return;
    }

    printf("Процент заполнения    | Объем памяти (разреженная) | Объем памяти (стандартная) | Время (разреженная) | Время (стандартная)\n");
    printf("-----------------------------------------------------------------------------------------------------------------------------\n");

    for (int fill_percentage = 10; fill_percentage <= 100; fill_percentage += 10) {
        // Выделяем память для разреженной и стандартной матриц
        int *sparseA = (int *)malloc(n * m *m * sizeof(int));
        int *IA = (int *)malloc((n + 1) * m * sizeof(int));
        int *JA = (int *)malloc(n * m * n * sizeof(int));
        int *standardA = (int *)malloc(n * m * n * sizeof(int));

        if (sparseA == NULL || IA == NULL || JA == NULL || standardA == NULL) {
            printf("Ошибка выделения памяти.\n");
            return;
        }

        fill_sparse_matrix(sparseA, IA, JA, n, m, fill_percentage);
        fill_standard_matrix(standardA, n, m, fill_percentage);

        int *vec = (int *)malloc(m * sizeof(int));
        int *sparseResult = (int *)malloc(n * sizeof(int));
        int *standardResult = (int *)malloc(n * sizeof(int));

        if (vec == NULL || sparseResult == NULL || standardResult == NULL) {
            printf("Ошибка выделения памяти для векторов и результатов.\n");
            free(sparseA);
            free(IA);
            free(JA);
            free(standardA);
            return;
        }

        int nonzero_count = IA[n];
        size_t sparseMemory = sizeof(int) * nonzero_count;
        size_t standardMemory = sizeof(int) * n * m;

        for (int i = 0; i < m; i++) {
            vec[i] = random_percentage();
        }

        struct timespec start, end;
        clock_gettime(CLOCK_REALTIME, &start);  // Используем CLOCK_REALTIME
        multiply_sparse_matrix_to_vector(sparseA, IA, JA, vec, n, m, &sparseResult);
        clock_gettime(CLOCK_REALTIME, &end);
        double sparseTime = (end.tv_sec - start.tv_sec) * 1e9 + (end.tv_nsec - start.tv_nsec); // Пересчет в наносекунды

        clock_gettime(CLOCK_REALTIME, &start);
        multiply_matrix_to_vector(standardA, IA, JA, vec, n, m, m, &standardResult);
        clock_gettime(CLOCK_REALTIME, &end);
        double standardTime = (end.tv_sec - start.tv_sec) * 1e9 + (end.tv_nsec - start.tv_nsec); // Пересчет в наносекунды

        printf("%d%%\t\t\t%zu байт\t\t\t%zu байт\t\t\t%.6lf нс\t\t\t%.6lf нс\n", fill_percentage, sparseMemory, standardMemory, sparseTime, standardTime);

        // Освобождаем память для текущих матриц, векторов и результатов
        free(vec);
        free(sparseResult);
        free(standardResult);
        free(sparseA);
        free(IA);
        free(JA);
        free(standardA);
    }
    printf("------------------------------------------------------------------------------------------------------------------------\n");
}
