#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "arrstack.h"
#include "liststack.h"
#include "defines.h"
#include <time.h>
/*
Задание: Создать программу работы со стеком, выполняющую операции добавления, удаления элементов и вывод текущего состояния стека. Реализовать стек:
а) статическим массивом.
б) списком.
Ввести арифметическое выражение типа: число|знак| … число|знак| число. Вычислить значение выражения. (Приоритетность операций необязательна)
*/

void run_experiments();
int main(void) 
{
    srand(time(NULL));
    int rc;
    int choice;
    char *menu = "0 - выход из программы\n1 - вычислить арифметическое выражение (с использованием массива)\n2 - вычислить арифметическое выражение (с использованием списка)\n3 - добавить элемент в стек (с использованием массива)\n4 - удалить элемент из стека (с использованием массива)\n5 - вывести стек (с использованием массива)\n6 - добавить элемент в стек (с использованием списка)\n7 - удалить элемент из стека (с использованием списка)\n8 - вывести стек (с использованием списка)\n9 - Сравнить производительность\n10 - Вывести массив свободных областей памяти\n";
    rc = 0;
    char expression[1000];
    Arr_Stack *arr_stack = create_arr_stack();
    List_Stack *list_stack = create_list_stack();
    int element_to_add_arr;
    int element_to_add_list;
    int rc_2;
    while (1) 
    {
        char tmp[5];
        printf("%s", menu);
        printf("Выберите пункт меню: ");
        rc = scanf("%d", &choice);
        fgets(tmp, 5, stdin);
        if (rc != 1) {
            return CHOICE_ERROR;
        }
        switch (choice) {
            case 0:
                free_arr_stack(arr_stack);
                free_list_stack(list_stack);
                return 0;
            case 1:
                printf("Введите арифметическое выражение: \n");
                fgets(expression, 100, stdin);

                size_t len = strlen(expression);
                if (len > 0 && expression[len - 1] == '\n') {
                    expression[len - 1] = '\0';
                }
                int result = calculate_arr_stack(expression);
                printf("Результат: %d\n", result);
                break;
            case 2:
                printf("Введите арифметическое выражение: \n");
                fgets(expression, 100, stdin);
                len = strlen(expression);
                if (len > 0 && expression[len - 1] == '\n') {
                    expression[len - 1] = '\0';
                }
                result = calculate_list_stack(expression);
                printf("Результат: %d\n", result);
                break;
            case 3:
                printf("Введите элемент для добавления в стек (с использованием массива): ");
                if (scanf("%d", &element_to_add_arr) != 1) {
                    printf("Ошибка при вводе элемента.\n");
                } else 
                {
                    rc_2 = push_arr_stack(arr_stack, element_to_add_arr);
                    if (rc_2 != STACK_OVERFLOW_ERROR)
                    {
                        printf("Элемент %d добавлен в стек (с использованием массива).\n", element_to_add_arr);
                    }
                    else
                    {
                        printf("Невозможно добавить элемент в стек, переполнение\n");
                    }
                }
                break;
            case 4:
                // Опция для удаления элемента из стека (с использованием массива)
                rc_2 = pop_arr_stack(arr_stack);
                if (rc_2 != EMPTY_STACK_ERROR)
                {
                    printf("Элемент удален из стека (с использованием массива).\n");
                }
                else
                {
                    printf("Стек пуст, невозможно удалить элемент\n");
                }
                break;
            case 5:
                // Опция для вывода стека (с использованием массива)
                print_arr_stack(arr_stack);
                break;
            case 6:
                // Опция для добавления элемента в стек (с использованием списка)
                printf("Введите элемент для добавления в стек (с использованием списка): ");
                if (scanf("%d", &element_to_add_list) != 1) {
                    printf("Ошибка при вводе элемента.\n");
                } else {
                    push_list_stack(list_stack, element_to_add_list);
                    printf("Элемент %d добавлен в стек (с использованием списка).\n", element_to_add_list);
                }
                break;
            case 7:
                // Опция для удаления элемента из стека (с использованием списка)
                rc_2 = pop_list_stack(list_stack);
                if (rc_2 != EMPTY_STACK_ERROR)
                {
                    printf("Элемент удален из стека (с использованием списка).\n");
                }
                else
                {
                    printf("Стек пуст, невозможно удалить элемент\n");
                }
                break;
            case 8:
                // Опция для вывода стека (с использованием списка)
                print_list_stack(list_stack);
                break;
            case 9:
                // Вызываем функцию для сравнения производительности
                run_experiments();
                break;
            case 10:
            // Вывод массива свободных областей
                print_free_memory_blocks();
            break;
            default:
                printf("Неверный пункт меню\n");
                rc = 0;
                break;
        }
    }
}
void run_experiments() {
    char expression[1000]; // Максимальная длина выражения - 1000 символов
    int iterations = 10000; // Количество экспериментов

    printf("%-9s | %-12s | %-19s | %-21s | %-29s | %s\n",
        "Операция", "Размер Stack", "Память (Array List)", "Память (Linked List)", "Время (наносекунды) (Array List)", "Время (наносекунды)(Linked List)");
    printf("------------------------------------------------------------------------------------------------------------------------------------------\n");

    char *operations[] = {"+", "-", "*", "/"};
    int stack_sizes[] = {10, 50, 100, 1000};

    for (int i = 0; i < 4; i++) { // Перебираем операции
        for (int j = 0; j < 4; j++) { // Перебираем размеры стека
            double total_time_array = 0.0;
            double total_time_list = 0.0;
            size_t memory_usage_array = 0;
            size_t memory_usage_list = 0;

            for (int k = 0; k < iterations; k++) {
                int stack_size = stack_sizes[j];
                snprintf(expression, sizeof(expression), "1 %s 2", operations[i]);
                for (int l = 0; l < stack_size - 4; l++) {
                    snprintf(expression + strlen(expression), sizeof(expression) - strlen(expression), " %s 3", operations[i]);
                }
                char *clean_expression = malloc(strlen(expression) + 1);
                int clean_index = 0;
                for (int m = 0; expression[m] != '\0'; m++) {
                    if (expression[m] != ' ') {
                        clean_expression[clean_index++] = expression[m];
                    }
                }
                clean_expression[clean_index] = '\0';

                struct timespec start, end;
                clock_gettime(CLOCK_MONOTONIC, &start);
                calculate_arr_stack(clean_expression);
                clock_gettime(CLOCK_MONOTONIC, &end);
                long long elapsed_ns = (end.tv_sec - start.tv_sec) * BILLION + (end.tv_nsec - start.tv_nsec);
                total_time_array += (double)elapsed_ns;
                memory_usage_array += (stack_size * sizeof(int) + strlen(clean_expression) + 1);

                free(clean_expression); 
            }

            for (int k = 0; k < iterations; k++) {
                int stack_size = stack_sizes[j];
                snprintf(expression, sizeof(expression), "1 %s 2", operations[i]);
                for (int l = 0; l < stack_size - 3; l++) {
                    snprintf(expression + strlen(expression), sizeof(expression) - strlen(expression), " %s 3", operations[i]);
                }
                char *clean_expression = malloc(strlen(expression) + 1);
                int clean_index = 0;
                for (int m = 0; expression[m] != '\0'; m++) {
                    if (expression[m] != ' ') {
                        clean_expression[clean_index++] = expression[m];
                    }
                }
                clean_expression[clean_index] = '\0';
                struct timespec start, end;
                clock_gettime(CLOCK_MONOTONIC, &start);
                calculate_list_stack(clean_expression);
                clock_gettime(CLOCK_MONOTONIC, &end);
                long long elapsed_ns = (end.tv_sec - start.tv_sec) * BILLION + (end.tv_nsec - start.tv_nsec);
                total_time_list += (double)elapsed_ns;
                memory_usage_list += (stack_size * sizeof(int) + strlen(clean_expression) + 1);

                free(clean_expression); 
            }

            double average_time_array = total_time_array / iterations;
            double average_time_list = total_time_list / iterations;

            printf("%-9s | %-12d | %-19lu | %-21lu | %-29.6f | %.6f\n", operations[i], stack_sizes[j], memory_usage_array, memory_usage_list, average_time_array, average_time_list);
        }
    }
}
