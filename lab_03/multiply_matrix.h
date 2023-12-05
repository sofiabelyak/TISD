#ifndef MULTIPLY_MATRIX_
#define MULTIPLY_MATRIX__

#include <stdio.h>
#include <stdlib.h>

#include "error.h"
#include "input_matrix.h"

/**
 * Умножает разреженную матрицу на вектор и сохраняет результат в массиве c.
 *
 * @param Val Указатель на массив значений разреженной матрицы.
 * @param Row Указатель на массив индексов строк разреженной матрицы.
 * @param Col Указатель на массив индексов столбцов разреженной матрицы.
 * @param vec Указатель на вектор, на который производится умножение.
 * @param n   Количество строк в матрице.
 * @param nv  Размер вектора.
 * @param c   Указатель на указатель, куда будет сохранен результат умножения.
 */
void multiply_sparse_matrix_to_vector(int *Val, int *Row, int *Col, int *vec, int n, int nv, int **c);

/**
 * Умножает стандартную матрицу на вектор и сохраняет результат в массиве c.
 *
 * @param A  Указатель на массив значений стандартной матрицы.
 * @param IA Указатель на массив индексов строк стандартной матрицы.
 * @param JA Указатель на массив индексов столбцов стандартной матрицы.
 * @param v  Указатель на вектор, на который производится умножение.
 * @param n  Количество строк в матрице.
 * @param m  Количество столбцов в матрице.
 * @param nv Размер вектора.
 * @param c  Указатель на указатель, куда будет сохранен результат умножения.
 */
void multiply_matrix_to_vector(int *A, int *IA, int *JA, int *v, int n, int m, int nv, int **c);


#endif