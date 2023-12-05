#ifndef _LISTSTACK_H_
#define _LISTSTACK_H_
#include <stdio.h>
#include <stdlib.h>
#include "defines.h"
/**
 * @struct Node
 * @brief Структура для представления узла в стеке на основе списка.
 */
typedef struct Node {
    int value;          /**< Значение элемента в узле. */
    struct Node *next;  /**< Указатель на следующий узел. */
} Node;

typedef struct {
    Node *Stack_Pointer; /**< Указатель на вершину стека. */
    int curr_size;       /**< Текущий размер стека. */
    int max_size;        /**< Максимальный размер стека. */
} List_Stack;

typedef struct FreeMemoryBlock {
    void* address;
    size_t size;
    struct FreeMemoryBlock* next;
} FreeMemoryBlock;

/**
 * @fn List_Stack *create_list_stack()
 * @brief Создает и инициализирует стек на основе списка.
 *
 * @return Указатель на созданный стек на основе списка или NULL в случае ошибки.
 */
List_Stack *create_list_stack();
/**
 * @fn Node *create_node(int value)
 * @brief Создает и инициализирует узел списка с заданным значением.
 *
 * @param value Значение, которое должно быть установлено в узле.
 * @return Указатель на созданный узел или NULL в случае ошибки.
 */
Node *create_node(int value);
/**
 * @fn int push_list_stack(List_Stack *stack, int value)
 * @brief Добавляет элемент в стек на основе списка.
 *
 * @param stack Указатель на стек на основе списка.
 * @param value Элемент для добавления в стек.
 * @return 0 в случае успешного добавления, иначе ошибка.
 */
int push_list_stack(List_Stack *stack, int value);
/**
 * @fn int pop_list_stack(List_Stack *stack)
 * @brief Удаляет и возвращает элемент из стека на основе списка.
 *
 * @param stack Указатель на стек на основе списка.
 * @return Удаленный элемент или ошибка в случае пустого стека.
 */
int pop_list_stack(List_Stack *stack);
/**
 * @fn void free_list_stack(List_Stack *stack)
 * @brief Освобождает память, выделенную для стека на основе списка и его узлов.
 *
 * @param stack Указатель на стек на основе списка.
 */
void free_list_stack(List_Stack *stack);
/**
 * @fn void print_list_stack(const List_Stack *stack)
 * @brief Выводит информацию о стеке на основе списка, включая элементы, адреса и использованную память.
 *
 * @param stack Указатель на стек на основе списка.
 */
void print_list_stack(const List_Stack *stack);
/**
 * @fn int is_operator(char c)
 * @brief Проверяет, является ли символ оператором (+, -, *, /).
 *
 * @param c Символ для проверки.
 * @return 1, если символ является оператором, иначе 0.
 */
int is_operator(char c);
/**
 * @fn int perform_operation(int operand1, int operand2, char operator)
 * @brief Выполняет операцию между двумя операндами с использованием заданного оператора.
 *
 * @param operand1 Первый операнд.
 * @param operand2 Второй операнд.
 * @param operator Оператор (+, -, *, /).
 * @return Результат операции между операндами.
 */
int perform_operation(int operand1, int operand2, char operator);

/**
 * @fn void print_free_memory_blocks()
 * @brief Выводит информацию о свободных блоках памяти.
 */
void print_free_memory_blocks();

/**
 * @fn void add_free_memory_block(void* address, size_t size)
 * @brief Добавляет информацию о свободном блоке памяти.
 *
 * @param address Адрес свободного блока памяти.
 * @param size    Размер свободного блока памяти.
 */
void add_free_memory_block(void* address, size_t size);
/**
 * @fn int calculate_list_stack(char *expression)
 * @brief Вычисляет результат выражения, используя стек на основе связанного списка.
 *
 * @param expression Строка, представляющая математическое выражение.
 * @return Результат вычисления выражения.
 */
int calculate_list_stack(char *expression);
/**
 * @fn int is_empty_list_stack(List_Stack *stack)
 * @brief Проверяет, пуст ли стек на основе списка.
 *
 * @param stack Указатель на стек.
 */
int is_empty_list_stack(List_Stack *stack);
#endif