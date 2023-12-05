#include <string.h>
#include "calc.h"
#include "errs.h"

// Функция для сдвига элементов массива влево
void shift_array_left(int *arr, size_t arr_s, size_t shift)
{
    for (size_t i = 0; i < arr_s; i++)
    {
        if (i < arr_s - shift)
        {
            // Если индекс i меньше разности размера массива и величины сдвига,
            // то копируем элементы на shift позиций влево
            arr[i] = arr[i + shift];
        }
        else
        {
            // Если индекс i больше или равен разности размера массива и величины сдвига,
            // то присваиваем элементу значение 0
            arr[i] = 0;
        }
    }
}

void take_null(struct my_float *lf)
{
    // Обнуляем массив mantiss путем заполнения нулями
    memset(lf->mantiss, 0, MAX_MANTISS_SIZE * sizeof(int));
    lf->order = 0; // Обнуляем порядок
    lf->size = 0; // Обнуляем размер
    lf->mant_sign = 0; // Устанавливаем знак мантиссы в положительное значение
}

// Функция умножения двух чисел с плавающей запятой
// и сохранения результата в третьем числе
int multiply(const struct my_float *first_float, const struct my_float *second_float, struct my_float *result_float, size_t max_mant_size)
{
    int arr[ARR_SIZE]; // Временный массив для хранения промежуточных результатов умножения
    size_t arr_s = 0; // Размер временного массива
    size_t ind = 0; // Индекс для обхода временного массива
    take_null(result_float); // Исходное значение результата равно нулю

    // Инициализация временного массива arr нулями
    for (size_t i = 0; i < ARR_SIZE; i++)
        arr[i] = 0;
    int abs_size = first_float->size + second_float->size;

    // Умножение каждой пары мантисс чисел
    for (size_t i = 0; i < first_float->size; i++) {
        for (size_t j = 0; j < second_float->size; j++) {
            arr[j+i] += first_float->mantiss[i] * second_float->mantiss[j];
            size_t k = i + j;

            // Если текущий элемент временного массива превышает CELL_BASE (обычно 10),
            // переносим его в следующий элемент
            while (arr[k] >= BASE && k < ARR_SIZE - 1) {
                arr[k + 1] += arr[k] / 10;
                arr[k] %= 10;
                k++;
            }
        }
    }
    // Определение размера временного массива arr_s
    while (ind < ARR_SIZE)
    {
        if (arr[ind] != 0)
        {
            arr_s = ind + 1;
        }
        ind++;
    }
    int order_add = (int)(arr_s) - abs_size;
    // Если размер временного массива превышает допустимый размер мантиссы,
    // необходимо выполнить сдвиг влево и изменить порядок числа.
    if (arr_s > max_mant_size)
    {
        size_t diff = arr_s - max_mant_size;
        for (size_t i = 0; i < diff; i++)
            if (arr[i] >= 5)
                arr[i + 1]++;
        for (size_t i = diff; i < arr_s && arr[i] > 9; i++)
        {
            arr[i] = 0;
            arr[i + 1]++;
        }
        // Поиск первой ненулевой цифры во временном массиве arr
        for (size_t i = diff;arr[i] == 0 && i < arr_s; i++)
            diff++;
        // Сдвиг всех элементов влево на diff позиций
        shift_array_left(arr, arr_s, diff);
        arr_s -= diff;
    }
    result_float->size = arr_s;

    // Определение знака результата
    result_float->mant_sign = (first_float->mant_sign != second_float->mant_sign) ? 0 : 1;

    if (first_float->size == 0 || second_float->size == 0)
        result_float->order = 0;
    else
        result_float->order += second_float->order + first_float->order + order_add;

    if (result_float->order > 99999 || result_float->order < -99999)
        return ERR_RANGE;
    for (size_t i = 0; i < arr_s; i++)
        result_float->mantiss[i] = arr[i];

    return ERR_OK; // Успешное выполнение функции
}
