#ifndef TEST_CHECK_H
#define TEST_CHECK_H
#include <stdbool.h>

/**
* @brief Программа проверяет модульные тесты ввода чисел и  функцию input_float
* @return Результат выполнения:
* - ERR_RANGE - неверные значения мантиссы и/или порядка..
* - ERR_OK - успешное выполнение.
*/
bool testInputFloat();

#endif
