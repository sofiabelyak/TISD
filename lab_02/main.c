#include <windows.h>
#include <time.h>
#include "theater.h"
#include "sortbytable.h"
#include "sortkeys.h"
#include "print.h"
#include "stdio.h"
#include "errors.h"
#include "test_check.h"

TheaterPlay *theater_plays;
int num_records = 0;
int max_records = 1001;

int main(void)
{
    system("chcp 65001");
    theater_plays = (TheaterPlay *) malloc(max_records * sizeof(TheaterPlay));
    if (theater_plays == NULL)
    {
        printf("Ошибка выделения памяти.\n");
        return EMPTY_FILE_ERROR;
    }
    int *theater_keys = (int *) malloc(max_records * sizeof(int));
    if (theater_keys == NULL)
    {
        printf("Ошибка выделения памяти для theater_keys.\n");
        return EMPTY_FILE_ERROR;
    }
    // Запуск модульных тестов
    //runTests();
    int choice;
    while (1) {
        printf("+-----------------------------------------------------------+\n");
        printf("|                 Меню управления данными                   |\n");
        printf("+-----------------------------------------------------------+\n");
        printf("| 0 - Выйти из программы                                    |\n");
        printf("| 1 - Прочитать файл                                        |\n");
        printf("| 2 - Вывести данные                                        |\n");
        printf("| 3 - Вывести таблицу ключей                                |\n");
        printf("| 4 - Добавить запись                                       |\n");
        printf("| 5 - Удалить запись                                        |\n");
        printf("| 6 - Отсортировать по цене (быстрая сортировка)            |\n");
        printf("| 7 - Отсортировать по цене (медленная сортировка)          |\n");
        printf("| 8 - Отсортировать таблицу ключей (быстрая сортировка)     |\n");
        printf("| 9 - Отсортировать таблицу ключей (медленная сортировка)   |\n");
        printf("| 10 - Вывести данные по таблице ключей                     |\n");
        printf("| 11 - Вывести таблицу эффективности                        |\n");
        printf("| 12 - Вывести список балетов для детей                     |\n");
        printf("+-----------------------------------------------------------+\n");
        scanf("%d", &choice);
        char age_range[5];
        char max_duration[10];
        FILE *file = NULL;
        char filename[100];
        switch (choice)
        {
            case 0:
                free(theater_plays);
                free(theater_keys);
                return ERR_OK;
            case 1:
                printf("Введите название файла\n");
                scanf("%s", filename);
                file = fopen(filename, "r");
                if (file == NULL) {
                    printf("Ошибка %d: Не удалось открыть файл. Убедитесь, что файл существует.\n", OPEN_FILE_ERROR);
                    return OPEN_FILE_ERROR;
                }
                while (fscanf(file, "%s %s %f %f %d",
                              theater_plays[num_records].theater_name,
                              theater_plays[num_records].play,
                              &theater_plays[num_records].ticket_price,
                              &theater_plays[num_records].max_price,
                              &theater_plays[num_records].play_type) == 5) {
                    num_records++;
                    if (num_records >= max_records)
                    {
                        printf("Ошибка %d: Достигнуто максимальное количество записей.\n", OVERFLOW_ERROR);
                        return OVERFLOW_ERROR;
                    }
                    // Читаем оставшиеся поля в зависимости от типа спектакля
                    if (theater_plays[num_records - 1].play_type == 4)
                    {
                        fscanf(file, "%s", theater_plays[num_records - 1].details.fairy_tale.age_range);
                    } else if (theater_plays[num_records - 1].play_type == 5)
                    {
                        fscanf(file, "%s %s %d %s %s",
                               theater_plays[num_records - 1].details.musical.composer,
                               theater_plays[num_records - 1].details.musical.country,
                               &theater_plays[num_records - 1].details.musical.performance_type,
                               theater_plays[num_records - 1].details.musical.age_range,
                               theater_plays[num_records - 1].details.musical.duration);
                    }
                }
                fclose(file);

                // После чтения данных инициализируем theater_keys
                for (int i = 0; i < num_records; i++)
                {
                    theater_keys[i] = i;
                }
                printf("Данные из файла прочитаны успешно.\n");
                break;

            case 2:
                if (num_records == 0) {
                    printf("Ошибка %d: Нет данных для вывода.\n", EMPTY_FILE_ERROR);
                    return EMPTY_FILE_ERROR;
                } else {
                    printTable();
                }
                break;
            case 3:
                if (num_records == 0) {
                    printf("Ошибка %d: Нет данных для вывода таблицы ключей.\n", EMPTY_FILE_ERROR);
                    break;
                } else {
                    printf("+-------+-------------------+\n");
                    printf("|  Индекс   |  Цена билета  |\n");
                    printf("+-------+-------------------+\n");
                    for (int i = 0; i < num_records; i++) {
                        int index = theater_keys[i]; // Получаем исходный индекс из массива ключей
                        printf("|    %-3d    |     %-9.2f |\n", index + 1, theater_plays[index].ticket_price);
                        printf("+-------+-------------------+\n");
                    }
                }
                break;
            case 4:
                addRecord();
                break;
            case 5:
                deleteRecord();
                break;
            case 6:
            {
                quickSortByTicketPrice(0, num_records - 1);
                printf("Данные быстро отсортированы по цене билетов.\n");
            }
                break;
            case 7:
            {
                slowSortByTicketPrice();
                printf("Данные медленно отсортированы по цене билетов.\n");
            }
                break;
            case 8:
                quickSortByKey(0, num_records - 1, theater_keys, theater_plays);
                printf("Таблица ключей быстро отсортирована по цене билетов.\n");
                break;
            case 9:
                slowSortByKey(num_records, theater_keys, theater_plays);
                printf("Таблица ключей медленно отсортирована по цене билетов.\n");
                break;
            case 10:
                if (num_records == 0) {
                    printf("Ошибка %d: Нет данных для вывода.\n", EMPTY_FILE_ERROR);
                } else {
                    printf("+-------+-----------------+-----------------+--------------+-------------+------------+-------------------+-----------+\n");
                    printf("|  N  |   Театр    |Спектакль |  Цена  | Макс цена |Тип| Возраст| Композитор |   Страна   |Тип выступления| Время (ч) |\n");
                    printf("+-------+-----------------+-----------------+--------------+-------------+------------+-------------------+-----------+\n");
                    for (int i = 0; i < num_records; i++) {
                        int index = theater_keys[i]; // Получаем исходный индекс из таблицы ключей
                        printf("| %-3d | %-10s | %-8s | %-6.2f |   %-6.2f  | %-1d | %-6s | %-10s | %-10s |     %-7d   |   %-6s  |\n",
                               index + 1, // Индекс записи (начиная с 1)
                               theater_plays[index].theater_name, theater_plays[index].play, theater_plays[index].ticket_price,
                               theater_plays[index].max_price, theater_plays[index].play_type,
                               (theater_plays[index].play_type == 4) ? theater_plays[index].details.fairy_tale.age_range :
                               (theater_plays[index].play_type == 5) ? theater_plays[index].details.musical.age_range : "", // Поле Возраст
                               (theater_plays[index].play_type == 4) ? "" :
                               (theater_plays[index].play_type == 5) ? theater_plays[index].details.musical.composer : "", // Поле Композитор
                               theater_plays[index].details.musical.country,
                               (theater_plays[index].play_type == 4) ? 0 :
                               (theater_plays[index].play_type == 5) ? theater_plays[index].details.musical.performance_type : 0, // Поле Тип выступления
                               (theater_plays[index].play_type == 4) ? "" :
                               (theater_plays[index].play_type == 5) ? theater_plays[index].details.musical.duration : ""); // Поле Продолжительность
                        printf("+-------+-----------------+-----------------+--------------+-------------+------------+-------------------+-----------+\n");
                    }
                }
                break;
            case 11:
            {
                printf("Измерение времени выполнения сортировок для данных и таблицы ключей...\n");

                struct timespec quickSortDataStart, quickSortDataEnd;
                struct timespec slowSortDataStart, slowSortDataEnd;
                struct timespec quickSortKeyStart, quickSortKeyEnd;
                struct timespec slowSortKeyStart, slowSortKeyEnd;

                long long quickSortDataTimeSum = 0;
                long long slowSortDataTimeSum = 0;
                long long quickSortKeyTimeSum = 0;
                long long slowSortKeyTimeSum = 0;

                for (int i = 0; i < 500; i++)
                {
                    // Измерение времени выполнения быстрой сортировки данных
                    clock_gettime(CLOCK_MONOTONIC, &quickSortDataStart);
                    quickSortByTicketPrice(0, num_records - 1);
                    clock_gettime(CLOCK_MONOTONIC, &quickSortDataEnd);
                    quickSortDataTimeSum += (quickSortDataEnd.tv_sec - quickSortDataStart.tv_sec) * 1000000000LL +
                                            (quickSortDataEnd.tv_nsec - quickSortDataStart.tv_nsec);

                    // Измерение времени выполнения медленной сортировки данных
                    clock_gettime(CLOCK_MONOTONIC, &slowSortDataStart);
                    slowSortByTicketPrice();
                    clock_gettime(CLOCK_MONOTONIC, &slowSortDataEnd);
                    slowSortDataTimeSum += (slowSortDataEnd.tv_sec - slowSortDataStart.tv_sec) * 1000000000LL +
                                           (slowSortDataEnd.tv_nsec - slowSortDataStart.tv_nsec);

                    // Измерение времени выполнения быстрой сортировки ключей
                    clock_gettime(CLOCK_MONOTONIC, &quickSortKeyStart);
                    quickSortByKey(0, num_records - 1, theater_keys, theater_plays);
                    clock_gettime(CLOCK_MONOTONIC, &quickSortKeyEnd);
                    quickSortKeyTimeSum += (quickSortKeyEnd.tv_sec - quickSortKeyStart.tv_sec) * 1000000000LL +
                                           (quickSortKeyEnd.tv_nsec - quickSortKeyStart.tv_nsec);

                    // Измерение времени выполнения медленной сортировки ключей
                    clock_gettime(CLOCK_MONOTONIC, &slowSortKeyStart);
                    slowSortByKey(num_records, theater_keys, theater_plays);
                    clock_gettime(CLOCK_MONOTONIC, &slowSortKeyEnd);
                    slowSortKeyTimeSum += (slowSortKeyEnd.tv_sec - slowSortKeyStart.tv_sec) * 1000000000LL +
                                          (slowSortKeyEnd.tv_nsec - slowSortKeyStart.tv_nsec);
                }

                // Рассчитываем среднее время выполнения
                long long averageQuickSortDataTime = quickSortDataTimeSum / 500;
                long long averageSlowSortDataTime = slowSortDataTimeSum / 500;
                long long averageQuickSortKeyTime = quickSortKeyTimeSum / 500;
                long long averageSlowSortKeyTime = slowSortKeyTimeSum / 500;

                // Выводим средние значения в таблицу
                printf("Среднее время выполнения (наносекунды):\n");
                printf("+----------------------+-----------------------+\n");
                printf("|     Сортировка             |      Время      |\n");
                printf("+----------------------+-----------------------+\n");
                printf("| Быстрая сортировка         | %-14lld |\n", averageQuickSortDataTime);
                printf("| Медленная сортировка       | %-14lld |\n", averageSlowSortDataTime);
                printf("| Быстрая сортировка ключей  | %-14lld |\n", averageQuickSortKeyTime);
                printf("| Медленная сортировка ключей| %-14lld |\n", averageSlowSortKeyTime);
                printf("+----------------------+----------------------+\n");

                // Оценка использования оперативной памяти
                size_t memory_used = num_records * sizeof(TheaterPlay); // Размер данных
                size_t memory_used_keys = num_records * sizeof(int);     // Размер таблицы ключей
                printf("Использование оперативной памяти:\n");
                printf("Размер данных: %zu байт\n", memory_used);
                printf("Размер таблицы ключей: %zu байт\n", memory_used_keys);
                printf("Общий объем используемой памяти: %zu байт\n", memory_used + memory_used_keys);
                break;
            }
            case 12:
                printf("Введите возраст для поиска балетов: ");
                scanf("%s", age_range);
                printf("Введите максимальную продолжительность: ");
                scanf("%s", max_duration);
                printBalletsForChildrenWithDuration(age_range, max_duration);
                break;
            default:
                printf("Ошибка %d: Неверный выбор. Попробуйте снова.\n", CHOICE_ERROR);
                return CHOICE_ERROR;
        }
    }
}
