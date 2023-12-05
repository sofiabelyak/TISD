#include "sortkeys.h"

void sortKeysByTicketPrice(int num_records, int theater_keys[])
{
    for (int i = 0; i < num_records; i++)
    {
        theater_keys[i] = i;
    }
    qsort(theater_keys, num_records, sizeof(int), compareTheaterByTicketPrice);
}

void quickSortByKey(int left, int right, int theater_keys[], TheaterPlay theater_plays[])
{
    if (left < right) {
        int i = left, j = right;
        float pivot = theater_plays[theater_keys[left]].ticket_price; // Используем цену билетов как опорный элемент

        while (i <= j) {
            // Ищем элементы, которые больше или равны опорному элементу
            while (theater_plays[theater_keys[i]].ticket_price < pivot) {
                i++;
            }
            // Ищем элементы, которые меньше или равны опорному элементу
            while (theater_plays[theater_keys[j]].ticket_price > pivot) {
                j--;
            }
            if (i <= j) {
                int temp = theater_keys[i];
                theater_keys[i] = theater_keys[j];
                theater_keys[j] = temp;
                i++;
                j--;
            }
        }
        // Рекурсивно сортируем две подгруппы
        if (left < j) {
            quickSortByKey(left, j, theater_keys, theater_plays);
        }
        if (i < right) {
            quickSortByKey(i, right, theater_keys, theater_plays);
        }
    }
}

// Ваша функция медленной сортировки для таблицы ключей
void slowSortByKey(int num_records, int theater_keys[], TheaterPlay theater_plays[])
{
    for (int i = 0; i < num_records - 1; i++) {
        for (int j = 0; j < num_records - i - 1; j++) {
            if (theater_plays[theater_keys[j]].ticket_price > theater_plays[theater_keys[j + 1]].ticket_price) {
                int temp = theater_keys[j];
                theater_keys[j] = theater_keys[j + 1];
                theater_keys[j + 1] = temp;
            }
        }
    }
}