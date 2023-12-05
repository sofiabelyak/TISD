#include "sortbytable.h"

// Функция для сортировки записей по цене билета (быстрая сортировка)
void quickSortByTicketPrice(int left, int right)
{
    if (left < right)
    {
        int i = left, j = right;
        float pivot = theater_plays[left].ticket_price;

        while (i <= j) {
            while (theater_plays[i].ticket_price < pivot)
            {
                i++;
            }
            while (theater_plays[j].ticket_price > pivot) {
                j--;
            }
            if (i <= j) {
                TheaterPlay temp = theater_plays[i];
                theater_plays[i] = theater_plays[j];
                theater_plays[j] = temp;
                i++;
                j--;
            }
        }
        quickSortByTicketPrice(left, j);
        quickSortByTicketPrice(i, right);
    }
}


void slowSortByTicketPrice()
{
    for (int i = 0; i < num_records - 1; i++) {
        for (int j = 0; j < num_records - i - 1; j++) {
            if (theater_plays[j].ticket_price > theater_plays[j + 1].ticket_price) {
                TheaterPlay temp = theater_plays[j];
                theater_plays[j] = theater_plays[j + 1];
                theater_plays[j + 1] = temp;
            }
        }
    }
}


int compareTheaterByTicketPrice(const void *a, const void *b)
{
    int indexA = *((int *) a);
    int indexB = *((int *) b);

    float priceA = theater_plays[indexA].ticket_price;
    float priceB = theater_plays[indexB].ticket_price;

    if (priceA < priceB) return -1;
    if (priceA > priceB) return 1;
    return 0;
}
