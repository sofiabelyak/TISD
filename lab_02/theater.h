#ifndef THEATER_H
#define THEATER_H
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include "errors.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char theater_name[50];
    char play[50];
    float ticket_price;
    float max_price; // Новое поле для максимальной цены
    int play_type;
    union {
        struct {
            char age_range[5];
        } fairy_tale;  // Для сказок
        struct {
            char age_range[5];
            char composer[50];
            char country[50];
            int performance_type;
            char duration[10];
        } musical;  // Для музыкальных спектаклей
    } details;
} TheaterPlay;
extern TheaterPlay *theater_plays;
extern int num_records;
extern int max_records;

bool isValidAgeRange(const char *age_range);
/**
 * @brief Проверяет, содержит ли строка числа.
 * Эта функция проверяет, содержит ли входная строка `str` какие-либо числа.
 * @param str Строка для проверки.
 * @return 1, если строка содержит числа, и 0 в противном случае.
 */
int containsNumbers(const char *str);
/**
 * @brief Добавляет новую запись о театральном представлении.
 * Эта функция запрашивает у пользователя данные о театральном представлении и добавляет их в массив `theater_plays`.
 * @return ERR_OK, если запись успешно добавлена, или соответствующий код ошибки в противном случае.
 */
int addRecord();
/**
 * @brief Удаляет записи о театральных представлениях по выбранному полю и значению.
 * Эта функция позволяет пользователю выбрать поле для удаления записей и ввести значение, по которому производится поиск и удаление записей.
 */
void deleteRecord();
#endif
