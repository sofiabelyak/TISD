#ifndef PRINT_H__
#define PRINT_H__
#include <stdio.h>
#include <stdlib.h>
#include "error.h"
/**
 * Выводит матрицу вектор-строку на консоль.
 *
 * @param A Указатель на массив значений.
 * @param n Количество элементов в массиве.
 */
void print_matrix_to_vector(int *A, int n);

/**
 * Выводит матрицу на консоль.
 *
 * @param A Указатель на массив значений матрицы.
 * @param n Количество строк в матрице.
 * @param m Количество столбцов в матрице.
 */
void print_matrix(int *A, int n, int m);

#endif