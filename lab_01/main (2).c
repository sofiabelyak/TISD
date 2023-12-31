#include <stdio.h>
#include <string.h>
#include "float.h"
#include "calc.h"
#include "errs.h"
#include "print_result.h"
#include <windows.h>
#include "test_check.h"
int main(void)
{
    system("chcp 65001");
    int rc = ERR_OK; // Переменная для кода ошибки

    // Создание структур для хранения чисел и результата
    struct my_float first_float;
    struct my_float second_float;
    struct my_float result_float;

    // Панель для ввода чисел
    printf("Данная программа предназначена для умножения двух действительных чисел.\n");
    printf("Однако, есть определенные ограничения на формат вводимых чисел.\n");
    printf("Числа должны соответствовать формату:[+-]?[0-9]*[.]?[0-9]*E[+-][0-9]*.\n");
    printf("Знак перед мантиссой, порядком является необязательным, точка может отсутствовать, числа могут быть как до, так и после точки. Важно, чтобы хотя бы в одном месте (до или после точки) было число.\n");
    printf("Если используется символ E, то после него должна быть хотя бы одна цифра.\n");
    printf("Cуммарная длина мантиссы первого сомножителя до 35 значащих цифр, второго – до 40 значащих цифр, а величина порядка до 5");
    printf("-----------------------------------------------------------------------------------------------------------------------\n");

    // Ввод первого числа
    char input[50];
    printf("-------------------------------\n");
    printf("|    Введите первое число:    |\n");
    printf("-------------------------------\n");
    fgets(input, sizeof(input), stdin);
    size_t len;
    len = strlen(input);
    if (len && input[len - 1] == '\n')
    {
        input[len - 1] = 0;
        len--;
    }
    if (!len || len > MAX_FIRST_MANTISS_SIZE)
    {
        printf("|  Некорректная длина первого вводимого числа, длина должна соответствовать описанию   |\n");
        printf("|--------------------------------------------------------------------------------------|\n");
        return ERR_RANGE;
    }
    rc = input_float(input, &first_float, MAX_FIRST_MANTISS_SIZE, MAX_ORDER_SIZE);
    if (rc != ERR_OK)
    {
        printf("|     Некорректное набранное первое число, ввод должен соответствовать описанию     |\n");
        printf("|-----------------------------------------------------------------------------------|\n");
        return rc;
    }

    // Ввод второго числа
    printf("-------------------------------\n");
    printf("|    Введите второе число:     |\n");
    printf("-------------------------------\n");
    fgets(input, sizeof(input), stdin);
    len = strlen(input);
    if (len && input[len - 1] == '\n')
    {
        input[len - 1] = 0;
        len--;
    }
    if (!len || len > MAX_SECOND_MANTISS_SIZE)
    {
        printf("|  Некорректная длина второго вводимого числа, длина должна соответствовать описанию   |\n");
        printf("|--------------------------------------------------------------------------------------|\n");
        return ERR_RANGE;
    }
    rc = input_float(input, &second_float, MAX_SECOND_MANTISS_SIZE, MAX_ORDER_SIZE);
    if (rc != ERR_OK)
    {
        printf("|     Некорректное набранное второе число, ввод должен соответствовать описанию     |\n");
        printf("|-----------------------------------------------------------------------------------|\n");
        return rc;
    }
    // Умножение чисел
    rc = multiply(&first_float, &second_float, &result_float, MAX_RESULT_MANTISS_SIZE);
    if (rc != ERR_OK)
    {
        printf("Переполнение порядка в результате умножения.\n");
        return rc;
    }
    printf("------------------------------------\n");
    printf("|   Итоговый результат умножения:   |\n");
    printf("------------------------------------\n");

    // Вывод результата
    print_res(&result_float);
    testInputFloat();
    // Возвращение значения кода ошибки
    return rc;
}