#include "errors.h"

void error_print(int rc)
{
    switch (rc)
    {
        case 1:
            printf("Ошибка ввода.\n");
            break;
        case 2: 
            printf("Неправильный диапазон.\n");
            break;
        case 3: 
            printf("Ошибка памяти.\n");
            break;
        case 4: 
            printf("Ошибка при открытии файла.\n");
            break;
    }
}
