#include "float.h"
#include <stdio.h>

// Функция для печати значения my_float
void print_res(const struct my_float *result_float){
    // Печатаем знак мантиссы
    printf("%c0.", result_float->mant_sign == 1 ? '+' : '-');
    // Печатаем мантиссу в обратном порядке
    for (int i = result_float->size - 1; i >= 0; i--)
    {
        printf("%d", result_float->mantiss[i]);
    }
    // Печатаем знак порядка и значение порядка
    printf("E%c%d\n", result_float->order >= 0 ? '+' : ' ', result_float->order);
}
