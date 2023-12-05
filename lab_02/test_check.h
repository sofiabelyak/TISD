#ifndef TEST_CHECK_H
#define TEST_CHECK_H
#include <stdio.h>
#include <string.h>
#include "theater.h"
/**
 * @brief Тестирует функцию addRecord.
 * Этот тест проверяет функцию addRecord на добавление записи о театральном представлении в массив `theater_plays`.
 * @return 0 при успешном тесте, иначе 1.
 */
int testAddRecord();
/**
 * @brief Тестирует функцию deleteRecord.
 * Этот тест проверяет функцию deleteRecord на удаление записей о театральных представлениях из массива `theater_plays`.
 * @return 0 при успешном тесте, иначе 1.
 */
int testDeleteRecord();

/**
 * @brief Запускает все модульные тесты и выводит результаты.
 *
 * Эта функция запускает все модульные тесты и выводит количество пройденных и не пройденных тестов.
 */
void runTests();


#endif
