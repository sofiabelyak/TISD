#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include <sys/time.h>
#include <inttypes.h>
#define INITIAL_TABLE_SIZE 1000001
#define GROWTH_FACTOR 1.15

// Структура для узла хеш-таблицы
struct Node_hash 
{
    char word[100]; // Предполагается, что максимальная длина слова - 99 символов
    int occupied;   // Флаг, указывающий, занята ли ячейка
    struct Node_hash *next; // Указатель на следующий узел в случае коллизии
};
// Структура для хеш-таблицы
struct HashTable {
    struct Node_hash **table; // Указатель на массив указателей на узлы
    int currentTableSize;     // Текущий размер таблицы
};

/**
 * @brief Хеш-функция для вычисления хеш-кода строки.
 * 
 * @param word Строка, для которой вычисляется хеш-код.
 * @return unsigned int Хеш-код строки.
 */
unsigned int hash_function(const char *word);

/**
 * @brief Вычисляет коэффициент загрузки текущей хеш-таблицы.
 * 
 * @param hashtable Указатель на хеш-таблицу.
 * @return float Коэффициент загрузки.
 */
float load_factor(const struct HashTable *hashtable);

/**
 * @brief Производит реструктуризацию хеш-таблицы, изменяя её размер.
 * 
 * @param hashtable Указатель на хеш-таблицу.
 * @param new_size Новый размер хеш-таблицы.
 */
void restructure_table(struct HashTable *hashtable, int new_size);

/**
 * @brief Вставляет новый элемент в хеш-таблицу.
 * 
 * @param hashtable Указатель на хеш-таблицу.
 * @param word Строка, которую необходимо вставить.
 */
void insert_into_table(struct HashTable *hashtable, const char *word);

/**
 * @brief Выводит содержимое хеш-таблицы в консоль.
 * 
 * @param hashtable Указатель на хеш-таблицу.
 */
void display_table(const struct HashTable *hashtable);

/**
 * @brief Ищет элемент в хеш-таблице по ключу.
 * 
 * @param hashtable Указатель на хеш-таблицу.
 * @param word Ключ (строка) для поиска.
 * @param comparisons Указатель на переменную для хранения количества сравнений.
 * @return struct Node_hash* Указатель на найденный узел или NULL, если не найден.
 */
struct Node_hash *search_in_table(const struct HashTable *hashtable, const char *word, int *comparisons);
#endif