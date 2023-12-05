#include "efficiency.h"
#include "simulate.h"
void make_and_del_arr()
{
    arr_queue_t *queue = create_arr();
    while (queue->amount != MAXLEN)
    {
        task_t *task = create_task();
        push_arr(queue, task);
    }
    while (queue->amount != 0)
    {
        task_t *task = pop_arr(queue);
        delete_task(task);
    }
    delete_arr(queue);
}

void make_and_del_list()
{
    list_queue_t *queue = create_list();
    while (queue->amount != MAXLEN)
    {
        task_t *task = create_task();
        push_list(queue, task);
    }
    while (queue->amount != 0)
    {
        task_t *task = pop_list(queue);
        delete_task(task);
    }
    delete_list(queue);
}

void efficiency() {
    int64_t sum_simple, sum = 0;
    struct timeval tv_start, tv_stop;
    int count = 1000;
    printf("| Тип данных | Время (мс) | Память (байт) |\n");
    printf("|------------|------------|-------------- |\n");
    // Для массива
    for (int i = 0; i < count; i++) {
        gettimeofday(&tv_start, NULL);
        simulate_arr(0);
        gettimeofday(&tv_stop, NULL);
        sum_simple = (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL + (tv_stop.tv_usec - tv_start.tv_usec);
        sum += sum_simple;
    }
    printf("| Массив     | %-10" PRId64 " | %-13ld |\n", sum / count, sizeof(task_t) * MAXLEN + sizeof(int) * 5);
    // Для списка
    sum = 0;
    for (int i = 0; i < count; i++) {
        gettimeofday(&tv_start, NULL);
        simulate_list(0);
        gettimeofday(&tv_stop, NULL);
        sum_simple = (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL + (tv_stop.tv_usec - tv_start.tv_usec);
        sum += sum_simple;
    }
    printf("| Список     | %-10" PRId64 " | %-13ld |\n", sum / count, sizeof(node_t) * MAXLEN + sizeof(int) * 2);
}
