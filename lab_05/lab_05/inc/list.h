#ifndef _LISTQUEUE_H_

#include "task.h"
#include "defines.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct node node_t;

struct node
{
    task_t *task;
    node_t *next;
};

typedef struct
{
    node_t *Pin;
    node_t *Pout;
    int amount;
    int maxamount;

} list_queue_t;
/**
 * @brief Создает узел списка.
 * 
 * @param task Указатель на заявку, которую содержит узел.
 * 
 * @return Указатель на созданный узел или NULL в случае ошибки.
 */
node_t *create_node(task_t *task);

/**
 * @brief Создает списковую очередь.
 * 
 * @return Указатель на созданную очередь или NULL в случае ошибки.
 */
list_queue_t *create_list();

/**
 * @brief Удаляет списковую очередь и освобождает занимаемую ей память.
 * 
 * @param queue Указатель на списковую очередь.
 */
void delete_list(list_queue_t *queue);

/**
 * @brief Добавляет заявку в списковую очередь.
 * 
 * @param queue Указатель на списковую очередь.
 * @param task  Указатель на добавляемую заявку.
 * 
 * @return 0 в случае успешного добавления, OVERFLOW при переполнении,
 *         ALLOCATE в случае ошибки выделения памяти.
 */
int push_list(list_queue_t *queue, task_t *task);

/**
 * @brief Извлекает заявку из списковой очереди.
 * 
 * @param queue Указатель на списковую очередь.
 * 
 * @return Указатель на извлеченную заявку или NULL, если очередь пуста.
 */
task_t *pop_list(list_queue_t *queue);

/**
 * @brief Выводит информацию об элементах списковой очереди.
 * 
 * @param queue Указатель на списковую очередь.
 */
void print_list(list_queue_t *queue);


#define _LISTQUEUE_H_
#endif