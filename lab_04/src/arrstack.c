#include "arrstack.h"

Arr_Stack *create_arr_stack() 
{
    Arr_Stack *arr_stack = malloc(sizeof(Arr_Stack));
    if (arr_stack == NULL) 
    {
        return NULL;
    }
    arr_stack->curr_size = 0;
    return arr_stack;
}

int push_arr_stack(Arr_Stack *s, int value) 
{
    if (s->curr_size >= STACK_SIZE) 
    {
        return STACK_OVERFLOW_ERROR;
    }
    s->Stack_Start[s->curr_size] = value;
    s->curr_size++;
    return 0;
}

int pop_arr_stack(Arr_Stack *s) 
{
    if (s->curr_size == 0) 
    {
        return EMPTY_STACK_ERROR;
    }
    s->curr_size--;
    return s->Stack_Start[s->curr_size];
}

void free_arr_stack(Arr_Stack *s) 
{
    free(s);
}
int is_empty_arr_stack(Arr_Stack *stack) {
    return (stack->curr_size == 0);
}
void print_arr_stack(const Arr_Stack *stack) {
    if (stack->curr_size == 0) {
        printf("Стек пуст.\n");
        return;
    }
    printf("Содержимое стека (с использованием массива):\n");
    for (int i = stack->curr_size - 1; i >= 0; i--) {
    printf("Элемент %d: %d\n", stack->curr_size - 1 - i, stack->Stack_Start[i]);
    printf("Адрес элемента %d: %p\n", stack->curr_size - 1 - i, (void*)&stack->Stack_Start[i]);
}
    printf("Размер стека (массива): %d\n", stack->curr_size);
    printf("Занятая память (байты): %lu\n", (unsigned long)(stack->curr_size * sizeof(int)));
}

int calculate_arr_stack(const char *expression) {
    Arr_Stack *operand_stack = create_arr_stack(); // Создаем стек для операндов
    Arr_Stack *operator_stack = create_arr_stack(); // Создаем стек для операторов

    if (operand_stack == NULL || operator_stack == NULL) {
        printf("Ошибка выделения памяти для стеков.\n");
        exit(1);
    }
    size_t i, expr_len = strlen(expression);
    for (i = 0; i < expr_len; i++) {
        if (expression[i] == ' ') 
        {
            continue; // Пропускаем пробелы
        } 
        else if (isdigit(expression[i])) 
        { // Если символ - цифра
            int num = 0;
            while (i < expr_len && isdigit(expression[i])) {
                num = num * 10 + (expression[i] - '0'); // Преобразуем последовательность цифр в число
                i++;
            }
            push_arr_stack(operand_stack, num); // Помещаем число в стек операндов
        } 
        else if (is_operator(expression[i])) { // Если символ - оператор
            push_arr_stack(operator_stack, expression[i]); // Помещаем оператор в стек операторов
        } 
        else {
            printf("Недопустимый символ в выражении: %c\n", expression[i]); // Обнаружен недопустимый символ
            exit(1);
        }
    }
    while (!is_empty_arr_stack(operator_stack)) { // Пока стек операторов не пуст
        char operator = pop_arr_stack(operator_stack); // Извлекаем оператор
        int operand1 = pop_arr_stack(operand_stack); // Извлекаем первый операнд
        int operand2 = pop_arr_stack(operand_stack); // Извлекаем второй операнд
        int result = perform_operation(operand1, operand2, operator); // Выполняем операцию
        push_arr_stack(operand_stack, result); // Помещаем результат обратно в стек операндов
    }
    int result = pop_arr_stack(operand_stack); // Получаем окончательный результат
    free_arr_stack(operand_stack); // Освобождаем память, выделенную для стека операндов
    free_arr_stack(operator_stack); // Освобождаем память, выделенную для стека операторов
    return result; // Возвращаем окончательный результат вычислений
}
