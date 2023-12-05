#include "liststack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

FreeMemoryBlock* free_memory_blocks = NULL;

List_Stack *create_list_stack() {
    List_Stack *list_stack = malloc(sizeof(List_Stack));
    if (list_stack == NULL) {
        return NULL;
    }
    list_stack->Stack_Pointer = NULL;
    list_stack->curr_size = 0;
    list_stack->max_size = 1000; 
    return list_stack;
}

Node *create_node(int value) {
    Node *node = malloc(sizeof(Node));
    if (node == NULL) {
        return NULL;
    }
    node->value = value;
    node->next = NULL;
    return node;
}

int push_list_stack(List_Stack *stack, int value) {
    Node *node = create_node(value);
    if (node == NULL) {
        return ALLOCATE_ERROR; 
    }

    if (stack->curr_size >= stack->max_size) {
        stack->max_size *= 2;
    }

    node->next = stack->Stack_Pointer;
    stack->Stack_Pointer = node;
    stack->curr_size++;
    return 0;
}

void add_free_memory_block(void* address, size_t size) {
    FreeMemoryBlock* new_block = malloc(sizeof(FreeMemoryBlock));
    if (new_block == NULL) {
        return;
    }
    new_block->address = address;
    new_block->size = size;
    new_block->next = free_memory_blocks;
    free_memory_blocks = new_block;
}

void print_free_memory_blocks() {
    printf("Массив свободных областей памяти:\n");
    FreeMemoryBlock* current = free_memory_blocks;
    while (current != NULL) {
        printf("Адрес: %p, Размер: %lu байт\n", current->address, current->size);
        current = current->next;
    }
}

int pop_list_stack(List_Stack *stack) {
    if (stack->Stack_Pointer == NULL) {
        return EMPTY_STACK_ERROR; 
    }
    Node *tmp = stack->Stack_Pointer;
    stack->Stack_Pointer = stack->Stack_Pointer->next;
    int value = tmp->value;
    free(tmp);
    stack->curr_size--;
    return value;
}

void free_list_stack(List_Stack *stack) {
    Node *curr = stack->Stack_Pointer;
    Node *next;

    while (curr) {
        next = curr->next;
        free(curr);
        curr = next;
    }

    stack->curr_size = 0;
    free(stack);
}

void print_list_stack(const List_Stack *stack) {
    Node *curr = stack->Stack_Pointer;

    if (curr == NULL) {
        printf("Стек пуст.\n");
        return;
    }

    printf("Содержимое стека (с использованием списка):\n");
    int index = 0;
    while (curr) {
        printf("Элемент %d: %d\n", index, curr->value);
        printf("Адрес элемента %d: %p\n", index, (void*)curr);
        curr = curr->next;
        index++;
    }
    printf("Размер стека (списка): %d\n", index);
    printf("Занятая память (байты): %lu\n", (unsigned long)(index * sizeof(int)));
    printf("Освобожденные ячейки памяти: %lu\n", (unsigned long)((stack->max_size - index) * sizeof(int)));
}

int is_operator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

int perform_operation(int operand1, int operand2, char operator) {
    switch (operator) {
        case '+':
            return operand1 + operand2;
        case '-':
            return operand1 - operand2;
        case '*':
            return operand1 * operand2;
        case '/':
            if (operand2 == 0) {
                printf("Деление на ноль!\n");
                exit(1);
            }
            return operand1 / operand2;
        default:
            return 0;
    }
}

int is_empty_list_stack(List_Stack *stack) {
    return (stack->curr_size == 0);
}

int calculate_list_stack(char *expression) {
    List_Stack *num_stack = create_list_stack();
    List_Stack *operator_stack = create_list_stack();
    if (num_stack == NULL || operator_stack == NULL) {
        printf("Ошибка выделения памяти для стека.\n");
        exit(1);
    }
    char *token = strtok(expression, " ");
    while (token != NULL) {
        if (isdigit(token[0])) {
            int num = atoi(token);
            push_list_stack(num_stack, num);
        } else if (is_operator(token[0])) {
            char operator = token[0];
            push_list_stack(operator_stack, operator);
        }
        token = strtok(NULL, " ");
    }
    while (!is_empty_list_stack(operator_stack)) {
        char operator = (char)pop_list_stack(operator_stack);
        int operand1 = pop_list_stack(num_stack);
        int operand2 = pop_list_stack(num_stack);
        int result = perform_operation(operand1, operand2, operator);
        push_list_stack(num_stack, result);
    }

    int final_result = pop_list_stack(num_stack);

    free_list_stack(num_stack);
    free_list_stack(operator_stack);
    return final_result;
}
