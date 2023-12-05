#ifndef CALC_H__
#define CALC_H__
#include "float.h"

/**
* @brief Функция выполняет умножение двух структур my_float.
* Функция умножает два числа, представленные структурами my_float, и сохраняет результат в третью структуру my_float.
* @param[in] first_float Указатель на первое число.
* @param[in] second_float Указатель на второе число.
* @param[out] result_float Указатель на структуру, в которую будет сохранен результат умножения.
* @param[in] max_mant_size Максимальный размер мантиссы результата.
* @return Результат выполнения:
* - ERR_OK - успешное выполнение.
*/
int multiply(const struct my_float *first_float, const struct my_float *second_float, struct my_float *result_float, size_t max_mant_size);
/**
* @brief Функция инициализирует структуру my_float нулевыми значениями.
* Функция инициализирует все поля структуры my_float нулевыми значениями.
* @param[in,out] lf Указатель на структуру my_float, которую необходимо инициализировать.
*/
void take_null(struct my_float *lf);

/**
* @brief Функция сдвигает элементы массива влево на указанное количество позиций.
* Функция сдвигает элементы массива влево на указанное количество позиций. При этом элементы, выходящие за пределы массива, заменяются нулями.
* @param[in,out] arr Указатель на массив, который необходимо сдвинуть.
* @param[in] arr_s Размер массива.
* @param[in] shift Количество позиций, на которое необходимо сдвинуть элементы.
*/
void shift_array_left(int *arr, size_t arr_s, size_t shift);

#endif
