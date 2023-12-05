#include "list.h"


node_t *create_node(task_t *task)
{
    node_t *node = malloc(sizeof(node_t));
    if (node == NULL)
        return NULL;
    node->task = task;
    node->next = NULL;
    return node;
}

list_queue_t *create_list()
{
    list_queue_t *queue = malloc(sizeof(list_queue_t));
    if (queue == NULL)
        return NULL;
    queue->amount = 0;
    queue->maxamount = MAXLEN;
    queue->Pin = NULL;
    queue->Pout = NULL;
    
    return queue;
}

void delete_list(list_queue_t *queue)
{
    node_t *next;
    for ( ; queue->Pin; queue->Pin = next)
    {
        next = queue->Pin->next;
        delete_task(queue->Pin->task);
        free(queue->Pin);
    }
    free(queue);
}


int push_list(list_queue_t *queue, task_t *task)
{
    node_t *node = create_node(task);
    if (node == NULL)
        return ALLOCATE;
    if (queue->amount == queue->maxamount)
        return OVERFLOW;
    node->next = queue->Pin;
    queue->Pin = node;
    if (queue->amount == 0)
        queue->Pout = node;
    queue->amount++;

    return 0;
}


task_t *pop_list(list_queue_t *queue)
{
    if (queue->amount == 0)
        return NULL;
    task_t *task = queue->Pout->task;
    if (queue->amount == 1)
    {
        free(queue->Pin);
        queue->Pin = NULL;
        queue->Pout = NULL;
        queue->amount = 0;
        return task;
    }
    queue->amount--;
    node_t *tmp;
    node_t *curr = queue->Pin;
    while (curr->next){
        tmp = curr;
        curr = curr->next;
    }
    tmp->next = NULL;
    free(curr);
    queue->Pout = tmp;
    return task;
}


void print_list(list_queue_t *queue)
{
    node_t *curr = queue->Pin;
    for (int i = 0; curr; curr = curr->next, i++)
    {
        printf("Номер элемента: %d\n", i);
        printf("Адрес элемента: %p\n", (void *)curr->task);
    }
    printf("\n");
}

