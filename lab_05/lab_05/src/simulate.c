#include "simulate.h"

extern float q1_f_s, q1_f_f, q2_f_s, q2_f_f;
extern float q1_w_s, q1_w_f, q2_w_s, q2_w_f;

void print_simulation_results(const SimulationLog *log, const char *queue_name)
{
    printf("|------------------------------|\n");
    printf("|        Очередь %s             |\n", queue_name);
    printf("|------------------------------|\n");
    printf("| Вышедшие заявки: %8d    |\n", log->task_out_count);
    printf("| Вошедшие заявки: %8d    |\n", log->task_in_count);
    printf("| Неудачные заявки: %8d   |\n", log->failed_task_count);
    printf("| Текущая длина: %8d      |\n", log->total_length);
    printf("| Средняя длина: %8d      |\n", log->task_out_count != 0 ? log->total_length / log->task_out_count : log->task_in_count);
    printf("| Среднее время ожидания: %5.2f|\n", log->task_out_count != 0 ? (float)log->total_length / log->task_out_count : 0);
    printf("|------------------------------|\n\n");
}


void print_simulation_summary(float hold_time, float work_time, float q1_f_s, float q1_f_f, float q1_w_s, float q1_w_f, SimulationLog* log1, SimulationLog* log2)
{
    printf("Время ожидания: %f\n", hold_time);
    printf("Время работы: %f\n", work_time);
    printf("Общее время моделирования : %f\n", hold_time + work_time);

    float expected_time = (q1_f_f + q1_f_s) > (q1_w_f + q1_w_s) ? ((float)(q1_f_f + q1_f_s) / 2.0) * 1000 : ((float)(q1_w_f + q1_w_s) / 2.0) * 1000;

    printf("Ожидаемое теоретическое время: %f\n", expected_time);
    printf("Погрешность: %3.2f%%\n", fabs((hold_time + work_time - expected_time) / expected_time * 100));

    printf("Заявки 1-го типа: Вошедших: %d, Вышедших: %d, Неудачных: %d\n", log1->task_in_count, log1->task_out_count, log1->failed_task_count);
    printf("Заявки 2-го типа: Вошедших: %d, Вышедших: %d, Неудачных: %d\n", log2->task_in_count, log2->task_out_count, log2->failed_task_count);
    printf("Среднее время пребывания в очереди 1: %f\n", log1->task_out_count != 0 ? (hold_time + work_time) / log1->task_out_count : 0);
    printf("Среднее время пребывания в очереди 2: %f\n", log2->task_out_count != 0 ? (hold_time + work_time) / log2->task_out_count : 0);
}


void simulate_arr(int key)
{
    float fetch_time1 = 0;
    float fetch_time2 = 0;
    float work_time = 0;
    float hold_time = 0;
    float time_until_fetch1 = 0;
    float time_until_fetch2 = 0;
    float time_until_work = 0;
    arr_queue_t *queue1 = create_arr();
    arr_queue_t *queue2 = create_arr();
    SimulationLog log1 = { 0 };
    SimulationLog log2 = { 0 };
    while (log1.task_out_count != 1000)
    {
        if (time_until_fetch1 <= 0)
        {
            time_until_fetch1 = random_float(q1_f_s, q1_f_f);
            task_t *task = create_task();
            int rc = push_arr(queue1, task);
            if (rc == OVERFLOW)
            {
                log1.failed_task_count += 1;
                delete_task(task);
            }
            else if (rc == 0)
            {
                log1.task_in_count += 1;
            }
            fetch_time1 += time_until_fetch1;
        }
        if (time_until_fetch2 <= 0)
        {
            time_until_fetch2 = random_float(q2_f_s, q2_f_f);
            task_t *task = create_task();
            int rc = push_arr(queue2, task);
            if (rc == OVERFLOW)
            {
                log2.failed_task_count += 1;
                delete_task(task);
            }
            else if (rc == 0)
            {
                log2.task_in_count += 1;
            }
            fetch_time2 += time_until_fetch2;
        }
        if (time_until_work <= 0)
        {
            if (queue1->amount == 0 && queue2->amount == 0)
                hold_time += fmax(time_until_fetch1, time_until_fetch2);
            else
            {
                if (queue1->amount == 0 || (queue2->amount != 0 && random_float(0, 1) < 0.5))
                {
                    if (queue2->amount != 0)
                    {
                        task_t *task;
                        task = pop_arr(queue2);
                        time_until_work = random_float(q2_w_s, q2_w_f);
                        work_time += time_until_work;
                        log2.function_call_count += 1;
                        log2.task_out_count += 1;
                        log2.total_length += queue2->amount;
                        delete_task(task);
                    }
                }
                else if (queue1->amount != 0)
                {
                    task_t *task;
                    task = pop_arr(queue1);
                    time_until_work = random_float(q1_w_s, q1_w_f);
                    work_time += time_until_work;
                    log1.function_call_count += 1;
                    log1.task_out_count += 1;
                    log1.total_length += queue1->amount;
                    delete_task(task);
                }

                if (log1.task_out_count % 100 == 0)
                {
                    if (key)
                    {
                        print_simulation_results(&log1, "1");
                        print_simulation_results(&log2, "2");
                    }
                }
            }
        }
        float smallest_time = 0;
        if (time_until_work != 0 && time_until_fetch1 != 0 && time_until_fetch2 != 0)
            smallest_time = min(time_until_work, time_until_fetch1, time_until_fetch2);
        else
            smallest_time = max(time_until_work, time_until_fetch1, time_until_fetch2);
        time_until_work -= smallest_time;
        time_until_fetch1 -= smallest_time;
        time_until_fetch2 -= smallest_time;
    }
    if (key)
        print_simulation_summary(hold_time, work_time, q1_f_s, q1_f_f, q1_w_s, q1_w_f, &log1, &log2);
    delete_arr(queue1);
    delete_arr(queue2);
}


void simulate_list(int key)
{
    
    float fetch_time1 = 0;
    float fetch_time2 = 0;
    float work_time = 0;
    float hold_time = 0;
    float time_until_fetch1 = 0;
    float time_until_fetch2 = 0;
    float time_until_work = 0;

    list_queue_t *queue1 = create_list();
    list_queue_t *queue2 = create_list();
    SimulationLog log1 = { 0 };
    SimulationLog log2 = { 0 };

    while (log1.task_out_count != 1000)
    {
        if (time_until_fetch1 <= 0)
        {
            time_until_fetch1 = random_float(q1_f_s, q1_f_f);
            task_t *task = create_task();
            int rc = push_list(queue1, task);
            if (rc == OVERFLOW)
            {
                log1.failed_task_count += 1;
                delete_task(task);
            }
            else if (rc == 0)
            {
                log1.task_in_count += 1;
            }
            fetch_time1 += time_until_fetch1;
        }
        if (time_until_fetch2 <= 0)
        {
            time_until_fetch2 = random_float(q2_f_s, q2_f_f);
            task_t *task = create_task();
            int rc = push_list(queue2, task);
            if (rc == OVERFLOW)
            {
                log2.failed_task_count += 1;
                delete_task(task);
            }
            else if (rc == 0)
            {
                log2.task_in_count += 1;
            }
            fetch_time2 += time_until_fetch2;
        }

        if (time_until_work <= 0)
        {
            if (queue1->amount == 0 && queue2->amount == 0)
                hold_time += fmax(time_until_fetch1, time_until_fetch2);
            else
            {
                if (queue1->amount == 0 || (queue2->amount != 0 && random_float(0, 1) < 0.5))
                {
                    if (queue2->amount != 0)
                    {
                        task_t *task;
                        task = pop_list(queue2);
                        time_until_work = random_float(q2_w_s, q2_w_f);
                        work_time += time_until_work;
                        log2.function_call_count += 1;
                        log2.task_out_count += 1;
                        log2.total_length += queue2->amount;
                        delete_task(task);
                    }
                }
                else if (queue1->amount != 0)
                {
                    task_t *task;
                    task = pop_list(queue1);
                    time_until_work = random_float(q1_w_s, q1_w_f);
                    work_time += time_until_work;
                    log1.function_call_count += 1;
                    log1.task_out_count += 1;
                    log1.total_length += queue1->amount;
                    delete_task(task);
                }

                if (log1.task_out_count % 100 == 0)
                {
                   if (key)
                    {
                        print_simulation_results(&log1, "1");
                        print_simulation_results(&log2, "2");
                    }
                }
            }
        }
        float smallest_time = 0;
        if (time_until_work != 0 && time_until_fetch1 != 0 && time_until_fetch2 != 0)
            smallest_time = min(time_until_work, time_until_fetch1, time_until_fetch2);
        else
            smallest_time = max(time_until_work, time_until_fetch1, time_until_fetch2);
        time_until_work -= smallest_time;
        time_until_fetch1 -= smallest_time;
        time_until_fetch2 -= smallest_time;
    }
    if (key)
        print_simulation_summary(hold_time, work_time, q1_f_s, q1_f_f, q1_w_s, q1_w_f, &log1, &log2);
    delete_list(queue1);
    delete_list(queue2);
}

float random_float(float min, float max)
{
    if (min >= max)
        return min;
    
    return (float)rand() / RAND_MAX * (max - min) + min;
}

float max(float a, float b, float c) 
{
    return (a > b) ? ((a > c) ? a : c) : ((b > c) ? b : c);
}

float min(float a, float b, float c) 
{
    return (a < b) ? ((a < c) ? a : c) : ((b < c) ? b : c);
}