#ifndef _SIMULATE_H_
#include "arr.h"
#include "list.h"
#include "task.h"
#include "defines.h"
#include <math.h>
#include <stdio.h>
#include <sys/time.h>
#include <inttypes.h>

typedef struct
{
    int task_in_count;
    int task_out_count;
    int failed_task_count;
    int function_call_count;
    int total_length;
} SimulationLog;

/**
 * @brief Выводит результаты моделирования для определенной очереди.
 * 
 * @param log        Указатель на структуру, содержащую лог моделирования.
 * @param queue_name Название очереди (например, "1" или "2").
 */
void print_simulation_results(const SimulationLog *log, const char *queue_name);

/**
 * @brief Выводит сводку по результатам моделирования.
 * 
 * @param hold_time   Время ожидания.
 * @param work_time   Время работы.
 * @param q1_f_s      Время обработки заявок 1-го типа в очереди.
 * @param q1_f_f      Время обработки заявок 1-го типа в устройстве.
 * @param q1_w_s      Время ожидания заявок 1-го типа в очереди.
 * @param q1_w_f      Время ожидания заявок 1-го типа в устройстве.
 * @param log1        Указатель на лог для очереди 1.
 * @param log2        Указатель на лог для очереди 2.
 */
void print_simulation_summary(float hold_time, float work_time, float q1_f_s, float q1_f_f, float q1_w_s, float q1_w_f, SimulationLog* log1, SimulationLog* log2);

/**
 * @brief Моделирует работу системы с использованием массива для хранения очередей.
 * 
 * @param key Флаг вывода результатов моделирования (1 - выводить, 0 - не выводить).
 */
void simulate_arr(int key);

/**
 * @brief Моделирует работу системы с использованием списка для хранения очередей.
 * 
 * @param key Флаг вывода результатов моделирования (1 - выводить, 0 - не выводить).
 */
void simulate_list(int key);

/**
 * @brief Генерирует случайное вещественное число в заданном диапазоне.
 * 
 * @param min Минимальное значение.
 * @param max Максимальное значение.
 * 
 * @return Случайное вещественное число.
 */
float random_float(float min, float max);

/**
 * @brief Находит максимальное из трех чисел.
 * 
 * @param a Первое число.
 * @param b Второе число.
 * @param c Третье число.
 * 
 * @return Максимальное из трех чисел.
 */
float max(float a, float b, float c);

/**
 * @brief Находит минимальное из трех чисел.
 * 
 * @param a Первое число.
 * @param b Второе число.
 * @param c Третье число.
 * 
 * @return Минимальное из трех чисел.
 */
float min(float a, float b, float c);


#define _SIMULATE_H_
#endif