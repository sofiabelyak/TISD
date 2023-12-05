#ifndef FLOAT_H__
#define FLOAT_H__
#include <stddef.h>
#include "errs.h"


struct my_float
{
    int mantiss[MAX_MANTISS_SIZE];
    int size;
    int order;
    int mant_sign;
};

/**
* @brief Функция input_float преобразует строку, содержащую численное значение с плавающей точкой, в структуру my_float.
* Функция анализирует строку и извлекает мантиссу числа, порядок и знак числа.
* Значение мантиссы сохраняется в массиве mantiss структуры my_float, порядок сохраняется в переменной order.
* Если задано ограничение на размер мантиссы и/или порядка, функция проверяет, что размер не превышает ограничения.
* @param[in] str Указатель на строку, содержащую числовое значение с плавающей точкой.
* @param[out] first_float Указатель на структуру my_float, в которую будет сохранена информация.
* @param[in] max_mant_size Максимальный размер мантиссы.
* @param[in] max_order_size Максимальный размер порядка.
* @return Результат выполнения:
* - ERR_RANGE - неверные значения мантиссы и/или порядка.
* - ERR_MANTISS_SIZE - превышен размер мантиссы.
* - ERR_OK - успешное выполнение.
*/
int input_float(const char *str, struct my_float *first_float, int max_mant_size, int max_order_size);

#endif
