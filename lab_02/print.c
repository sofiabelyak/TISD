#include "print.h"


void printBalletsForChildrenWithDuration(char age_range[], char max_duration[])
{
    int found = 0; // Флаг для отслеживания наличия записей

    printf("+-----------------+-----------------+--------------+-------------+------------+-----------------+-----------------\n");
    printf("|  Театр    | Спектакль| Цена    |Макс.Цена| Тип | Возраст | Композитор   |  Страна   | Тип выступления | Продолжительность |\n");
    printf("+-----------------+-----------------+--------------+-------------+------------+-----------------+-----------------\n");
    for (int i = 0; i < num_records; i++)
    {
        if (theater_plays[i].play_type == 5 &&
            atoi(theater_plays[i].details.fairy_tale.age_range) >= atoi(age_range) &&
            atof(theater_plays[i].details.musical.duration) < atof(max_duration) &&
            (theater_plays[i].details.musical.performance_type == 1))
        {
            printf("| %-6s | %-8s | %-7.2f | %-7.2f | %-3d | %-7s | %-12s | %-9s | %-15d | %-17s |\n",
                   theater_plays[i].theater_name, theater_plays[i].play, theater_plays[i].ticket_price,
                   theater_plays[i].max_price, theater_plays[i].play_type, theater_plays[i].details.fairy_tale.age_range,
                   theater_plays[i].details.musical.composer, theater_plays[i].details.musical.country,
                   theater_plays[i].details.musical.performance_type, theater_plays[i].details.musical.duration);
            printf("+-----------------+-----------------+--------------+-------------+------------+-----------------+-----------------\n");
            found = 1; // Устанавливаем флаг, что данные найдены
        }
    }
    if (!found)
    {
        printf("Ничего не найдено.\n");
    }
}
void printTable()
{
    printf("+-------+-----------------+-----------------+--------------+-------------+------------+-------------------+--------------+\n");
    printf("|  N  |   Театр    |Спектакль |  Цена  |Макс.Цена|Тип| Возраст| Композитор |   Страна   |Тип выступления| Время (ч) |\n");
    printf("+-------+-----------------+-----------------+--------------+-------------+------------+-------------------+--------------+\n");
    for (int i = 0; i < num_records; i++) {
        printf("| %-3d | %-10s | %-8s | %-6.2f | %-6.2f | %-1d | %-6s | %-10s | %-10s |     %-7d   |   %-6s  |\n",
               i + 1, // Индекс записи (начиная с 1)
               theater_plays[i].theater_name, theater_plays[i].play, theater_plays[i].ticket_price, theater_plays[i].max_price,
               theater_plays[i].play_type,
               (theater_plays[i].play_type == 4) ? theater_plays[i].details.fairy_tale.age_range :
               (theater_plays[i].play_type == 5) ? theater_plays[i].details.musical.age_range : "", // Поле Возраст
               (theater_plays[i].play_type == 4) ? "" :
               (theater_plays[i].play_type == 5) ? theater_plays[i].details.musical.composer : "", // Поле Композитор
               theater_plays[i].details.musical.country,
               (theater_plays[i].play_type == 4) ? 0 :
               (theater_plays[i].play_type == 5) ? theater_plays[i].details.musical.performance_type : 0, // Поле Тип выступления
               (theater_plays[i].play_type == 4) ? "" :
               (theater_plays[i].play_type == 5) ? theater_plays[i].details.musical.duration : ""); // Поле Продолжительность
        printf("+-------+-----------------+-----------------+--------------+-------------+------------+-------------------+--------------+\n");
    }
}
