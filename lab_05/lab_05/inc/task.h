#ifndef _TASK_H_

#include <stdlib.h>

typedef struct
{
    int n;
} task_t;

/**
 * @brief Создает новую задачу.
 * 
 * @return Указатель на созданную задачу или NULL в случае ошибки выделения памяти.
 */
task_t *create_task();

/**
 * @brief Удаляет задачу и освобождает выделенную для нее память.
 * 
 * @param task Указатель на задачу, которую необходимо удалить.
 */
void delete_task(task_t *task);


#define _TASK_H_
#endif