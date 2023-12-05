#include "test_check.h"

// Функция для тестирования функции addRecord
int testAddRecord()
{
    TheaterPlay new_record;
    strcpy(new_record.theater_name, "Theater1");
    strcpy(new_record.play, "Play1");
    new_record.ticket_price = 100.0;
    new_record.play_type = 1;
    strcpy(new_record.details.fairy_tale.age_range, "3+"); // Обновленное поле

    num_records = 0;

    int result = addRecord(&new_record);
    int expected_result = 0; // Ожидаем успешное добавление
    if (result != expected_result) {
        printf("addRecord test failed\n");
        return 1; // Возвращаем 1 в случае неудачного теста
    }

    return 0; // Возвращаем 0 в случае успешного теста
}

// Обновленный тест для функции deleteRecord
int testDeleteRecord()
{
    num_records = 0;
    TheaterPlay record_to_delete;
    strcpy(record_to_delete.theater_name, "Theater1");
    strcpy(record_to_delete.play, "Play1");
    record_to_delete.ticket_price = 100.0;
    record_to_delete.play_type = 1;
    strcpy(record_to_delete.details.fairy_tale.age_range, "3+");

    // Добавляем запись
    int add_result = addRecord(&record_to_delete);
    if (add_result != 0) {
        printf("addRecord test failed: Unable to add record\n");
        return 1;
    }

    // Удаление записи, которая есть в массиве
    deleteRecord("Theater1");
    int expected_num_records = 0;
    if (num_records != expected_num_records) {
        printf("deleteRecord test failed: num_records=%d, expected=%d\n", num_records, expected_num_records);
        return 1; // Возвращаем 1 в случае неудачного теста
    }

    // Попытка удаления несуществующей записи
    num_records = 1;
    theater_plays[0] = record_to_delete;
    deleteRecord("Theater2");
    expected_num_records = 1;
    if (num_records != expected_num_records) {
        printf("deleteRecord test failed: num_records=%d, expected=%d\n", num_records, expected_num_records);
        return 1; // Возвращаем 1 в случае неудачного теста
    }
    return 0; // Возвращаем 0 в случае успешного теста
}

// Функция для запуска всех модульных тестов и вывода результатов
void runTests()
{
    int num_passed = 0;
    int num_failed = 0;

    // Вызываем тесты и подсчитываем результаты
    if (testAddRecord() == 0) {
        num_passed++;
    } else {
        num_failed++;
    }
    if (testDeleteRecord() == 0) {
        num_passed++;
    } else {
        num_failed++;
    }

    // Выводим результаты
    printf("Пройдено тестов: %d\n", num_passed);
    printf("Не пройдено тестов: %d\n", num_failed);
}
