#include "simulate.h"
#include "efficiency.h"
#include <stdio.h>
/**
 * Беляк С.С. ИУ7-32Б
 * @file main.c
 * @brief Основной файл программы с имитацией системы обработки заявок.
 * 
 * Программа позволяет проводить имитацию работы системы обработки заявок
 * с использованием двух типов очередей: массивом и списком. Также предоставляет
 * возможность оценить эффективность системы и выполнить ручные операции с очередями.
 * 
 */
float q1_f_s = 1, q1_f_f = 5, q2_f_s = 0, q2_f_f = 3;
float q1_w_s = 0, q1_w_f = 4, q2_w_s = 0, q2_w_f = 1;
void mode();
int main(void) 
{
    int choice;
    int rc;
    char *menu ="| Пункт |               Действие                    |\n"
                "|-------|-------------------------------------------|\n"
                "|   0   | Выход                                     |\n"
                "|   1   | Запустить симуляцию для очереди массивом  |\n"
                "|   2   | Запустить симуляцию для очереди списком   |\n"
                "|   3   | Оценка эффективности                      |\n"
                "|   4   | Ручной режим                              |\n"
                "|   5   | Изменить параметры симуляции              |\n"
                "|---------------------------------------------------|\n";

    while (1) {
        printf("Выберите пункт меню:\n");
        printf("%s", menu);
        rc = scanf("%d", &choice);
        if (rc != 1) {
            printf("Некорректное значение ввода\n");
            while (getchar() != '\n')  
                ;
            continue;
        } else {
            switch (choice) {
                case 0:
                    return 0;
                case 1:
                    simulate_arr(1);
                    break;
                case 2:
                    simulate_list(1);
                    break;
                case 3:
                    efficiency();
                    break;
                case 4:
                    mode();
                    break;
                case 5:
                    while (1) {
                        printf("Введите начало и конец интервала доставки в первую очередь (x y): ");
                        rc = scanf("%f%f", &q1_f_s, &q1_f_f);
                        if (rc != 2 || q1_f_s >= q1_f_f || q1_f_s < 0 || q1_f_f < 0) {
                            printf("Некорректный ввод! Пожалуйста, введите корректные значения.\n");
                            break;
                        }
                        printf("Введите начало и конец интервала доставки во вторую очередь (x y): ");
                        rc = scanf("%f%f", &q2_f_s, &q2_f_f);
                        if (rc != 2 || q2_f_s >= q2_f_f || q2_f_s < 0 || q2_f_f < 0) 
                        {
                            printf("Некорректный ввод! Пожалуйста, введите корректные значения.\n");
                            break;
                        }
                        printf("Введите начало и конец интервала выполнения заявки из первой очереди (x y): ");
                        rc = scanf("%f%f", &q1_w_s, &q1_w_f);
                        if (rc != 2 || q1_w_s >= q1_w_f || q1_w_s < 0 || q1_w_f < 0) {
                            printf("Некорректный ввод! Пожалуйста, введите корректные значения.\n");
                            break;
                        }
                        printf("Введите начало и конец интервала выполнения заявки из второй очереди (x y): ");
                        rc = scanf("%f%f", &q2_w_s, &q2_w_f);
                        if (rc != 2 || q2_w_s >= q2_w_f || q2_w_s < 0 || q2_w_f < 0) {
                            printf("Некорректный ввод! Пожалуйста, введите корректные значения.\n");
                            break;
                        }
                        break;
                    }
                    break;
                default:
                    printf("Некорректное значение ввода\n");
                    break;
            }
        }
    }

    return 0;
}
void mode()
{
    int choice;
    int rc;
    char *menu = "| Пункт |              Действие            |\n"
                "|-------|----------------------------------|\n"
                "|   1   | Добавить заявку в массив-очередь |\n"
                "|   2   | Добавить заявку в список-очередь |\n"
                "|   3   | Удалить заявку из массива-очереди|\n"
                "|   4   | Удалить заявку из списка-очереди |\n"
                "|   5   | Текущее состояние очередей       |\n"
                "|   0   | Выйти из меню                    |\n";


    arr_queue_t *arr_queue = create_arr();
    list_queue_t *list_queue = create_list();

    while (1)
    {
        printf("%s", menu);
        printf("Введите пункт меню:\n");
        rc = scanf("%d", &choice);
        if (rc != 1)
        {
            printf("Неверный пункт меню\n");
            while (getchar() != '\n')
                ;
            continue;
        }
        switch (choice)
        {
            case 1:
            {
                task_t *task = create_task();
                rc = push_arr(arr_queue, task);
                if (rc != 0)
                {
                    if (rc == OVERFLOW)
                    {
                        printf("Очередь переполнена!\n");
                    }
                    else if (rc == ALLOCATE)
                    {
                        printf("Ошибка выделения памяти\n");
                        return;
                    }
                }
                else
                {
                    printf("Адрес добавленного элемента: %p\n", (void *)(arr_queue->data + arr_queue->amount - 1));
                }
                break;
            }
            case 2:
            {
                task_t *task = create_task();
                rc = push_list(list_queue, task);
                if (rc != 0)
                {
                    if (rc == OVERFLOW)
                    {
                        printf("Очередь переполнена!\n");
                    }
                    else if (rc == ALLOCATE)
                    {
                        printf("Ошибка выделения памяти\n");
                        return;
                    }
                }
                else
                {
                    printf("Адрес добавленного элемента: %p\n", (void *)list_queue->Pin->task);
                }
                break;
            }
            case 3:
            {
                task_t *task = pop_arr(arr_queue);
                if (task == NULL)
                {
                    printf("Очередь пуста!\n");
                }
                else
                {
                    printf("Адрес удаленного элемента: %p\n", (void *)(arr_queue->data + arr_queue->amount));
                    delete_task(task);
                }
                break;
            }
            case 4:
            {
                task_t *task = pop_list(list_queue);
                if (task == NULL)
                {
                    printf("Очередь пуста!\n");
                }
                else
                {
                    printf("Адрес удаленного элемента: %p\n", (void *)task);
                }
                break;
            }
            case 5:
            {
                printf("Очередь массивом:\n");
                print_arr(arr_queue);
                printf("Очередь списоком:\n");
                print_list(list_queue);
                break;
            }
            case 0:
            {
                delete_arr(arr_queue);
                delete_list(list_queue);
                return;
            }
            default:
                printf("Неверный пункт меню\n");
                break;
        }
    }
}