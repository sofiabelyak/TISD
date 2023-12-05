#ifndef _ARRSTACK_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "defines.h"
#include "liststack.h"

/**
 * @struct Arr_Stack
 * @brief Структура для представления стека на основе массива.
 */
typedef struct {
    int Stack_Start[STACK_SIZE];
    int curr_size;
} Arr_Stack;
/**
 * @fn Arr_Stack *create_arr_stack()
 * @brief Создает и инициализирует стек на основе массива.
 *
 * @return Указатель на созданный стек на основе массива или NULL в случае ошибки.
 */
Arr_Stack *create_arr_stack();
/**
 * @fn int push_arr_stack(Arr_Stack *s, int value)
 * @brief Добавляет элемент в стек на основе массива.
 *
 * @param s Указатель на стек на основе массива.
 * @param value Элемент для добавления в стек.
 * @return 0 в случае успешного добавления, иначе ошибка.
 */
int push_arr_stack(Arr_Stack *s, int value);
/**
 * @fn int pop_arr_stack(Arr_Stack *s)
 * @brief Удаляет и возвращает элемент из стека на основе массива.
 *
 * @param s Указатель на стек на основе массива.
 * @return Удаленный элемент или ошибка в случае пустого стека.
 */
int pop_arr_stack(Arr_Stack *s);
/**
 * @fn void free_arr_stack(Arr_Stack *s)
 * @brief Освобождает память, выделенную для стека на основе массива.
 *
 * @param s Указатель на стек на основе массива.
 */
void free_arr_stack(Arr_Stack *s);
/**
 * @fn void print_arr_stack(const Arr_Stack *stack)
 * @brief Выводит информацию о стеке на основе массива, включая элементы, адреса и использованную память.
 *
 * @param stack Указатель на стек на основе массива.
 */
void print_arr_stack(const Arr_Stack *stack);
/**
 * @fn int calculate_arr_stack(const char *expression)
 * @brief Вычисляет арифметическое выражение, используя стек на основе массива.
 *
 * @param expression Строка, содержащая арифметическое выражение.
 * @return Результат вычисления выражения или ошибка.
 */
int calculate_arr_stack(const char *expression);
/**
 * @fn int is_empty_arr_stack(Arr_Stack *stack)
 * @brief Проверяет, пуст ли стек на основе массива.
 *
 * @param stack Указатель на стек.
 */
int is_empty_arr_stack(Arr_Stack *stack);

#define _ARRSTACK_H_
#endif