#ifndef SORTKYES_H
#define SORTKYES_H
#include "sortbytable.h"
void sortKeysByTicketPrice(int num_records, int theater_keys[]);
void quickSortByKey(int left, int right, int theater_keys[], TheaterPlay theater_plays[]);
// Функция для медленной сортировки таблицы ключей по цене билетов
void slowSortByKey(int num_records, int theater_keys[], TheaterPlay theater_plays[]);
#endif