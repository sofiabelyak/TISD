#ifndef _ARRQUEUE_H_

#include <stdlib.h>
#include <stdio.h>
#include "task.h"
#include "defines.h"

typedef struct
{
    task_t **data;
    int Pin;
    int Pout;
    int amount;
    int maxamount;
    int allocated;

} arr_queue_t;

/**
 * @brief Создает массивную очередь.
 * 
 * @return Указатель на созданную очередь или NULL в случае ошибки.
 */
arr_queue_t *create_arr();

/**
 * @brief Удаляет массивную очередь и освобождает занимаемую ей память.
 * 
 * @param queue Указатель на массивную очередь.
 */
void delete_arr(arr_queue_t *queue);

/**
 * @brief Добавляет заявку в массивную очередь.
 * 
 * @param queue Указатель на массивную очередь.
 * @param task  Указатель на добавляемую заявку.
 * 
 * @return 0 в случае успешного добавления, OVERFLOW при переполнении,
 *         ALLOCATE в случае ошибки выделения памяти.
 */
int push_arr(arr_queue_t *queue, task_t *task);

/**
 * @brief Извлекает заявку из массивной очереди.
 * 
 * @param queue Указатель на массивную очередь.
 * 
 * @return Указатель на извлеченную заявку или NULL, если очередь пуста.
 */
task_t *pop_arr(arr_queue_t *queue);

/**
 * @brief Выводит информацию об элементах массивной очереди.
 * 
 * @param queue Указатель на массивную очередь.
 */
void print_arr(arr_queue_t *queue);


#define _ARRQUEUE_H_
#endif