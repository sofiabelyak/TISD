#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "efficiency.h"

int main(void) 
{
    FILE *f = NULL;
    size_t cnt = 0;
    int choice;
    char input[100];
    char c;
    struct Node* root = NULL, *search = NULL;
    int rc;
    char *menu ="| Пункт |               Действие                    |\n"
                "|-------|-------------------------------------------|\n"
                "|   0   | Выход                                     |\n"
                "|   1   | Считать дерево из файла                   |\n"
                "|   2   | Добавить узел                             |\n"
                "|   3   | Удалить узел                              |\n"
                "|   4   | Вывести дерево                            |\n"
                "|   5   | Найти узел                                |\n"
                "|   6   | Найти и выделить слова на заданную букву  |\n"
                "|   7   | Оценка эффективности                      |\n"
                "|---------------------------------------------------|\n";

    while (1)
    {
        printf("Выберите пункт меню:\n");
        printf("%s", menu);
        rc = scanf("%d", &choice);
        fgets(input, sizeof(input), stdin);
        if (rc != 1) {
            printf("Некорректное значение ввода\n");
            while (getchar() != '\n')  
                ;
            continue;
        } else {
            switch (choice) {
                case 0:
                    free_tree(root);
                    return 0;
                case 1:
                    printf("Введите имя файла: ");
                    if (scanf("%s", input) != 1)
                    {
                        printf("Не введено имя файла\n");
                        break;
                    }
                    f = fopen(input, "r");
                    fgets(input, sizeof(input), stdin);
                    if (!f)
                    {
                        printf("Некорректное имя файла\n");
                        break;
                    }
                    free_tree(root);
                    root = NULL;
                    while (fscanf(f, "%s", input) != EOF)
                        root = insert_node(root, input);
                    fclose(f);
                    break;
                case 2:
                    printf("Введите слово: ");
                    if (scanf("%s", input) != 1)
                    {
                        printf("Некорректная строка\n");
                        break;
                    }
                    root = insert_node(root, input);
                    fgets(input, sizeof(input), stdin);
                    break;
                case 3:
                    printf("Введите слово: ");
                    if (scanf("%s", input) != 1)
                    {
                        printf("Некорректная строка\n");
                        break;
                    }
                    root = delete_node(root, input);
                    fgets(input, sizeof(input), stdin);
                    break;
                case 4:
                    if (!root)
                    {
                        printf("Пустое дерево\n");
                        break;
                    }
                    draw_tree(root, 0, 0);
                    draw_line(root);
                    break;
                case 5:
                    printf("Введите слово: ");
                    if (scanf("%s", input) != 1)
                    {
                        printf("Некорректная строка\n");
                        break;
                    }
                    search = find_node(root, input);
                    fgets(input, sizeof(input), stdin);
                    if (!search)
                    {
                        printf("Узел не найден\n");
                        break;
                    }
                    draw_tree(search, 0, 0);
                    break;
                case 6:
                    if (!root)
                    {
                        printf("Пустое дерево\n");
                        break;
                    }
                    printf("Введите символ: ");
                    if (scanf("%c", &c) != 1)
                    {
                        printf("Некорректный символ\n");
                        break;
                    }
                    fgets(input, sizeof(input), stdin);
                    cnt = 0;
                    set_colour_for_letter(root, c, &cnt);
                    printf("Количество: %lu\n", cnt);
                    break;
                case 7:
                    printf("Введите имя файла: ");
                    if (scanf("%s", input) != 1)
                    {
                        printf("Не введено имя файла\n");
                        break;
                    }
                    f = fopen(input, "r");
                    fgets(input, sizeof(input), stdin);
                    if (!f)
                    {
                        printf("Некорректное имя файла\n");
                        break;
                    }
                    start_tests(f);
                    fclose(f);
                    break;
                default:
                    printf("Некорректное значение ввода\n");
                    break;
            }
        }
    }

    return 0;
}
