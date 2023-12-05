#include "theater.h"
#include <stdbool.h>
bool isValidAgeRange(const char *age_range)
{
    size_t len = strlen(age_range);

    // Проверяем, что длина строки не менее 2 символов (минимум одна цифра и знак "+")
    if (len < 2) {
        return false;
    }

    // Проверяем, что последний символ - это "+"
    if (age_range[len - 1] != '+') {
        return false;
    }

    // Проверяем, что все символы до знака "+" являются цифрами
    for (size_t i = 0; i < len - 1; i++) {
        if (!isdigit(age_range[i])) {
            return false;
        }
    }

    // Если прошли все проверки, то возрастной диапазон считается корректным
    return true;
}
int containsNumbers(const char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (isdigit(str[i])) {
            return 1; // Строка содержит числа
        }
    }
    return 0; // Строка не содержит числа
}
// Функция для добавления записи
int addRecord()
{
    if (num_records < max_records) {
        TheaterPlay new_record;
        printf("Введите название театра: ");
        scanf("%s", new_record.theater_name);
        printf("Введите название спектакля: ");
        scanf("%s", new_record.play);
        printf("Введите цену билета: ");
        if (scanf("%f", &new_record.ticket_price) != 1 || new_record.ticket_price < 0.0) {
            printf("Ошибка ввода. Введите действительное положительное число для цены билета.\n");
            // Очистить буфер ввода
            while (getchar() != '\n');
            return ERR_RANGE; // Вернуть код ошибки
        }
        printf("Введите макс.цену билета: ");
        if (scanf("%f", &new_record.max_price) != 1 || new_record.max_price < 0.0) {
            printf("Ошибка ввода. Введите действительное положительное число для цены билета.\n");
            // Очистить буфер ввода
            while (getchar() != '\n');
            return ERR_RANGE; // Вернуть код ошибки
        }
        printf("Введите тип спектакля (1: пьеса, 2: драма, 3: комедия, 4: сказка, 5: музыкальный): ");
        if (scanf("%d", &new_record.play_type) != 1 || (new_record.play_type < 1 || new_record.play_type > 5)) {
            printf("Ошибка ввода. Введите целое число от 1 до 5 для типа спектакля.\n");
            // Очистить буфер ввода
            while (getchar() != '\n');
            return ERR_RANGE; // Вернуть код ошибки
        }

        if (new_record.play_type == 4)
        {
            printf("Введите возрастной диапазон (например, 3+, 10+, 16+): ");
            scanf("%s", new_record.details.fairy_tale.age_range);
            if (!isValidAgeRange(new_record.details.fairy_tale.age_range))
            {
                printf("Ошибка ввода. Неверный формат возрастного диапазона.\n");
                return ERR_RANGE; // Вернуть код ошибки
            }
        }
        else
        {
            strcpy(new_record.details.fairy_tale.age_range, ""); // Очистить поле возрастного диапазона
        }

        if (new_record.play_type == 5)
        {
            printf("Введите имя композитора: ");
            scanf("%s", new_record.details.musical.composer);
            if (containsNumbers(new_record.details.musical.composer)) {
                printf("Ошибка ввода. Имя композитора не должно содержать числа.\n");
                return ERR_RANGE; // Вернуть код ошибки
            }
            printf("Введите страну: ");
            scanf("%s", new_record.details.musical.country);
            if (containsNumbers(new_record.details.musical.country)) {
                printf("Ошибка ввода. Название страны не должно содержать числа.\n");
                return ERR_RANGE; // Вернуть код ошибки
            }
            printf("Введите тип выступления (1: балет, 2: опера, 3: мюзикл): ");
            if (scanf("%d", &new_record.details.musical.performance_type) != 1 ||
                (new_record.details.musical.performance_type < 1 || new_record.details.musical.performance_type > 3)) {
                printf("Ошибка ввода. Введите целое число от 1 до 3 для типа выступления.\n");
                // Очистить буфер ввода
                while (getchar() != '\n');
                return ERR_RANGE; // Вернуть код ошибки
            }
            printf("Введите возрастной диапазон (например, 3+, 10+, 16+): ");
            scanf("%s", new_record.details.musical.age_range);
            // Проверка на корректность ввода age_range
            if (!isValidAgeRange(new_record.details.musical.age_range))
            {
                printf("Ошибка ввода. Неверный формат возрастного диапазона.\n");
                return ERR_RANGE; // Вернуть код ошибки
            }
            printf("Введите продолжительность: ");
            scanf("%s", new_record.details.musical.duration);
        }
        else
        {
            strcpy(new_record.details.musical.composer, ""); // Очистить поле композитора
            strcpy(new_record.details.musical.country, ""); // Очистить поле страны
            new_record.details.musical.performance_type = 0; // Сбросить тип выступления
            strcpy(new_record.details.musical.duration, ""); // Очистить поле продолжительности
        }
        theater_plays[num_records++] = new_record;
        printf("Запись добавлена успешно.\n");
        return ERR_OK; // Успешное добавление
    }
    else
    {
        printf("Достигнуто максимальное количество записей.\n");
        return OVERFLOW_ERROR; // Вернуть код ошибки
    }
}


// Функция для удаления записи
void deleteRecord() {
    int fieldToDelete;
    printf("Выберите поле для удаления записей:\n");
    printf("1 - Название театра\n");
    printf("2 - Название спектакля\n");
    printf("3 - Цена билета\n");
    printf("4 - Тип спектакля\n");
    printf("5 - Возрастной диапазон\n");
    printf("6 - Имя композитора\n");
    printf("7 - Страна\n");
    printf("8 - Тип выступления\n");
    printf("9 - Продолжительность\n");
    scanf("%d", &fieldToDelete);

    char valueToDelete[50];
    printf("Введите значение для удаления записей: ");
    fflush(stdin);

    if (fgets(valueToDelete, sizeof(valueToDelete), stdin) != NULL) {
        // Убираем символ новой строки из считанной строки
        size_t len = strlen(valueToDelete);
        if (len > 0 && valueToDelete[len - 1] == '\n') {
            valueToDelete[len - 1] = '\0';
        }

        int found = 0;
        for (int i = 0; i < num_records; i++) {
            switch (fieldToDelete) {
                case 1:
                    if (strcmp(theater_plays[i].theater_name, valueToDelete) == 0) {
                        // Запись соответствует введенному значению в выбранном поле, удаляем ее
                        for (int j = i; j < num_records - 1; j++) {
                            theater_plays[j] = theater_plays[j + 1];
                        }
                        num_records--;
                        printf("Записи, содержащие \"%s\" в поле \"Название театра\", успешно удалены.\n",
                               valueToDelete);
                        found = 1;
                        i--; // Проверяем текущую запись заново, так как после сдвига индексы изменились
                    }
                    break;
                case 2:
                    if (strcmp(theater_plays[i].play, valueToDelete) == 0) {
                        // Запись соответствует введенному значению в выбранном поле, удаляем ее
                        for (int j = i; j < num_records - 1; j++) {
                            theater_plays[j] = theater_plays[j + 1];
                        }
                        num_records--;
                        printf("Записи, содержащие \"%s\" в поле \"Название спектакля\", успешно удалены.\n",
                               valueToDelete);
                        found = 1;
                        i--; // Проверяем текущую запись заново, так как после сдвига индексы изменились
                    }
                    break;
                case 3:
                    if (fabs(theater_plays[i].ticket_price - atof(valueToDelete)) < 0.001) {
                        // Запись соответствует введенному значению в выбранном поле, удаляем ее
                        for (int j = i; j < num_records - 1; j++) {
                            theater_plays[j] = theater_plays[j + 1];
                        }
                        num_records--;
                        printf("Записи, содержащие \"%s\" в поле \"Цена билета\", успешно удалены.\n", valueToDelete);
                        found = 1;
                        i--; // Проверяем текущую запись заново, так как после сдвига индексы изменились
                    }
                    break;
                case 4:
                    if (theater_plays[i].play_type == atoi(valueToDelete)) {
                        // Запись соответствует введенному значению в выбранном поле, удаляем ее
                        for (int j = i; j < num_records - 1; j++) {
                            theater_plays[j] = theater_plays[j + 1];
                        }
                        num_records--;
                        printf("Записи, содержащие \"%s\" в поле \"Тип спектакля\", успешно удалены.\n", valueToDelete);
                        found = 1;
                        i--; // Проверяем текущую запись заново, так как после сдвига индексы изменились
                    }
                    break;
                case 5:
                    if (strcmp(theater_plays[i].details.fairy_tale.age_range, valueToDelete) == 0) {
                        // Запись соответствует введенному значению в выбранном поле, удаляем ее
                        for (int j = i; j < num_records - 1; j++) {
                            theater_plays[j] = theater_plays[j + 1];
                        }
                        num_records--;
                        printf("Записи, содержащие \"%s\" в поле \"Возрастной диапазон\", успешно удалены.\n",
                               valueToDelete);
                        found = 1;
                        i--; // Проверяем текущую запись заново, так как после сдвига индексы изменились
                    }
                    break;
                case 6:
                    if (strcmp(theater_plays[i].details.musical.composer, valueToDelete) == 0) {
                        // Запись соответствует введенному значению в выбранном поле, удаляем ее
                        for (int j = i; j < num_records - 1; j++) {
                            theater_plays[j] = theater_plays[j + 1];
                        }
                        num_records--;
                        printf("Записи, содержащие \"%s\" в поле \"Имя композитора\", успешно удалены.\n",
                               valueToDelete);
                        found = 1;
                        i--; // Проверяем текущую запись заново, так как после сдвига индексы изменились
                    }
                    break;
                case 7:
                    if (strcmp(theater_plays[i].details.musical.country, valueToDelete) == 0) {
                        // Запись соответствует введенному значению в выбранном поле, удаляем ее
                        for (int j = i; j < num_records - 1; j++) {
                            theater_plays[j] = theater_plays[j + 1];
                        }
                        num_records--;
                        printf("Записи, содержащие \"%s\" в поле \"Страна\", успешно удалены.\n", valueToDelete);
                        found = 1;
                        i--; // Проверяем текущую запись заново, так как после сдвига индексы изменились
                    }
                    break;
                case 8:
                    if (theater_plays[i].details.musical.performance_type == atoi(valueToDelete)) {
                        // Запись соответствует введенному значению в выбранном поле, удаляем ее
                        for (int j = i; j < num_records - 1; j++) {
                            theater_plays[j] = theater_plays[j + 1];
                        }
                        num_records--;
                        printf("Записи, содержащие \"%s\" в поле \"Тип выступления\", успешно удалены.\n",
                               valueToDelete);
                        found = 1;
                        i--; // Проверяем текущую запись заново, так как после сдвига индексы изменились
                    }
                    break;
                case 9:
                    if (strcmp(theater_plays[i].details.musical.duration, valueToDelete) == 0) {
                        // Запись соответствует введенному значению в выбранном поле, удаляем ее
                        for (int j = i; j < num_records - 1; j++) {
                            theater_plays[j] = theater_plays[j + 1];
                        }
                        num_records--;
                        printf("Записи, содержащие \"%s\" в поле \"Продолжительность\", успешно удалены.\n",
                               valueToDelete);
                        found = 1;
                        i--; // Проверяем текущую запись заново, так как после сдвига индексы изменились
                    }
                    break;
                default:
                    printf("Ошибка: Неверный выбор поля.\n");
                    return;
            }
        }

        if (!found) {
            printf("Записи с указанным значением в поле не найдены.\n");
        }
    }
    else
    {
        printf("Ошибка ввода.\n");
    }
}
