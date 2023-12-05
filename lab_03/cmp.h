#ifndef CMP_H__
#define CMP_H__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "error.h"
#include "input_matrix.h"
#include "multiply_matrix.h"

/**
 * Генерирует случайное число в диапазоне [0, 100].
 *
 * @return Сгенерированное случайное число.
 */
int random_percentage();

/**
 * Заполняет разреженную матрицу случайными значениями.
 *
 * @param A              Указатель на массив значений разреженной матрицы.
 * @param IA             Указатель на массив индексов строк.
 * @param JA             Указатель на массив индексов столбцов.
 * @param n              Количество строк в матрице.
 * @param m              Количество столбцов в матрице.
 * @param fill_percentage Процент заполнения матрицы ненулевыми значениями.
 */
void fill_sparse_matrix(int *A, int *IA, int *JA, int n, int m, int fill_percentage);

/**
 * Заполняет стандартную матрицу случайными значениями.
 *
 * @param A              Указатель на массив значений стандартной матрицы.
 * @param n              Количество строк в матрице.
 * @param m              Количество столбцов в матрице.
 * @param fill_percentage Процент заполнения матрицы ненулевыми значениями.
 */
void fill_standard_matrix(int *A, int n, int m, int fill_percentage);

/**
 * Сравнивает время выполнения операций умножения разреженной и стандартной матриц на вектор.
 * Выводит результаты сравнения в форматированной таблице.
 */
void compare_matrix_operations();


#endif