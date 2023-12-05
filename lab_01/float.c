#include "float.h"
#include "errs.h"
#include "calc.h"
#include <stddef.h>
// Функция парсит строку и сохраняет число с плавающей точкой в структуру
int input_float(const char *str, struct my_float *first_float, int max_mant_size, int max_order_size) {
    int mant_size = 0; // Размер мантиссы
    int zeros_new = 0;
    int decimal = 0;
    int order_size = 0; // Размер порядка
    int curr_zeros = 0; // Количество текущих нулей
    int zero_cnt = 0; // Количество нулей
    int zero_after_cnt = 0;
    int encountered_decimal = 0; // Флаг для обозначения, что встретили десятичную точку
    const char *ptr = str; // Указатель на текущий символ строки
    char order_sign = 1, sign = 1; // Флаги для обозначения знака порядка и мантиссы

    if ((*ptr) == '-')
    {
        sign = 0;
        ptr++;
    }
    if ((*ptr) == '+')
    {
        ptr++;
    }
    while (*ptr == '0' || *ptr == '.')
    {
        if (*ptr == '0')
        {
            ptr++;
            if (encountered_decimal)
                zero_after_cnt++;
            zeros_new = 1;
        }
        else
        {
            decimal = 1;
            ptr++;
            encountered_decimal = 1;

        }
    }
    const char *mant_end = NULL; // Указатель на последний символ мантиссы
    const char *curr = ptr; // Указатель на текущий символ
    while (*curr != '\0' && *curr != 'E')
    {
        if (*curr >= '0' && *curr <= '9')
        {
            mant_size += 1 + curr_zeros; // Увеличиваем размер мантиссы на количество текущих нулей
            mant_end = curr; // Обновляем указатель на последний символ мантиссы
            zero_cnt = 0; // Сбрасываем счетчик нулей
            curr_zeros = 0;
        }
        else if (*curr == '0')
        {
            curr_zeros++; // Увеличиваем количество текущих нулей
            if (!encountered_decimal)
            {
                zero_cnt++; // Увеличиваем количество нулей, если они находятся до десятичной точки
            }
            if(encountered_decimal && mant_size==0)
                zero_after_cnt++;
        }
        else if (*curr == '.' && !encountered_decimal)
        {
            encountered_decimal = 1; // Устанавливаем флаг, что встретили десятичную точку
        }
        else
        {
            return ERR_RANGE; // Если встретили некорректный символ, возвращаем ошибку
        }
        curr++; // Переходим к следующему символу
    }
    const char *order_ptr = NULL; // Указатель на начало порядка
    const char *order_end = NULL; // Указатель на конец порядка
    if (*curr == 'E')
    {
        int null_ord = 0;
        curr++; // Пропускаем символ 'E'
        if (*curr == '-')
        {
            order_sign = 0; // Устанавливаем флаг отрицательного порядка
            curr++;
        }
        if (*curr == '+')
        {
            curr++;
        }
        while (*curr == '0')
        {
            curr++; // Пропускаем ведущие нули в порядке
            null_ord = 1;
        }
        order_ptr = order_end = curr; // Устанавливаем указатели на начало порядка
        while (*curr != '\0')
        {
            if (*curr >= '0' && *curr <= '9')
            {
                order_size++; // Увеличиваем размер порядка
                order_end = curr; // Обновляем указатель на последний символ порядка
                curr++;
            }
            else
            {
                return ERR_RANGE; // Если встретили некорректный символ, возвращаем ошибку
            }
        }
        if (!null_ord && order_size == 0)
        {
            return ERR_RANGE; // Если порядок не содержит цифр, возвращаем ошибку
        }
    }
    int curr_mant = mant_size - 1; // Указатель на текущий символ мантиссы
    int order_add = 0; // Дополнительное значение порядка

    // Проверяем, что размеры мантиссы и порядка не превышают максимально допустимые значения
    if ((mant_size == 0 && zero_after_cnt && !zeros_new) || (mant_size > max_mant_size || order_size > max_order_size))
        return ERR_MANTISS_SIZE; // Если превышены, возвращаем ошибку
    take_null(first_float); // Обнуляем все поля структуры

    if (!decimal)
        encountered_decimal = 0; // Сбрасываем флаг десятичной точки
    // Проходим по строке и сохраняем цифры мантиссы
    for (const char *curr = ptr; curr <= mant_end; curr++)
    {
        if (*curr != '.')
        {
            if (!encountered_decimal)
                order_add++; // Увеличиваем дополнительное значение порядка, если еще не встретили десятичную точку
            first_float->mantiss[curr_mant] = (int)((*curr) - '0'); // Сохраняем цифру мантиссы
            curr_mant--;
        }
        else
        {
            encountered_decimal = 1; // Устанавливаем флаг десятичной точки
        }
    }
    if (order_size != 0)
    {
        int tmp = 0;
        const char *curr = order_ptr;
        while (curr <= order_end)
        {
            tmp *= 10;
            tmp += (int)((*curr) - '0'); // Преобразуем порядок из строки в целое число
            curr++;
        }
        if (!order_sign)
        {
            tmp = -tmp; // Устанавливаем знак порядка
        }
        first_float->order = tmp; // Сохраняем значение порядка
    }
    first_float->mant_sign = sign; // Сохраняем знак мантиссы
    first_float->size = mant_size; // Сохраняем размер мантиссы
    first_float->order += order_add + zero_cnt - zero_after_cnt; // Устанавливаем значение порядка
    return ERR_OK; // Возвращаем код успешного выполнения
}