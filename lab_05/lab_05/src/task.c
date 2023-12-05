#include "task.h"

task_t *create_task()
{
    task_t *task = malloc(sizeof(task_t));
    if (task == NULL)
        return NULL;
    return task;
}


void delete_task(task_t *task)
{
    free(task);
}