#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "efficiency.h"
#include "balance_tree.h"
#include "hash_table.h"

int main(void)
{
    struct HashTable hashtable;
    hashtable.currentTableSize = 0;
    hashtable.table = NULL;
    FILE *f = NULL;
    int choice;
    char input[100];
    struct Node *root = NULL, *search = NULL;
    int rc;
    char *menu = "| Пункт |               Действие                    |\n"
                 "|-------|-------------------------------------------|\n"
                 "|   0   | Выход                                     |\n"
                 "|   1   | Считать дерево из файла                   |\n"
                 //"|   2   | Добавить узел                             |\n"
                // "|   3   | Удалить узел                              |\n"
                 "|   2   | Вывести дерево                            |\n"
                 "|   3   | Найти слово в дереве                      |\n"
                 "|   4   | Сбалансировать дерево                     |\n"
                 "|   5   | Построить хеш-таблицу                     |\n"
                 "|   6   | Найти слово в хеш-таблице                 |\n"
                 "|   7   | Вывести хеш-таблицу                       |\n"
                 "|   8   | Оценка эффективности                      |\n"
                 "|   9   | Оценка эффективности реструктуризации     |\n"
                 "|---------------------------------------------------|\n";

    while (1)
    {
        printf("Выберите пункт меню:\n");
        printf("%s", menu);
        rc = scanf("%d", &choice);
        fgets(input, sizeof(input), stdin);
        if (rc != 1)
        {
            printf("Некорректное значение ввода\n");
            while (getchar() != '\n')
                ;
            continue;
        }
        else
        {
            switch (choice)
            {
            case 0:
                free_tree(root);
                free(hashtable.table);
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
            /*case 2:
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
            */
            case 2:
                if (!root)
                {
                    printf("Пустое дерево\n");
                    break;
                }
                draw_tree(root, 0, 0);
                draw_line(root);
                break;
            case 3:
                printf("Введите слово: ");
                if (scanf("%s", input) != 1)
                {
                    printf("Некорректная строка\n");
                    break;
                }
                int bc = 0;
                search = find_node(root, input, &bc);
                fgets(input, sizeof(input), stdin);
                if (!search)
                {
                    printf("Узел не найден\n");
                    break;
                }
                draw_tree(search, 0, 0);
                break;
            case 4:
                if (!root)
                {
                    printf("Пустое дерево\n");
                    break;
                }
                root = balance_tree(root);
                break;
            case 5:
                printf("Введите размерность хеш-таблицы: ");
                int tableSize;
                if (scanf("%d", &tableSize) != 1)
                {
                    printf("Некорректное значение ввода\n");
                    break;
                }
                for (int i = 0; i < hashtable.currentTableSize; i++)
                {
                    struct Node_hash *current = hashtable.table[i];
                    while (current != NULL)
                    {
                        struct Node_hash *next = current->next;
                        free(current);
                        current = next;
                    }
                    hashtable.table[i] = NULL;
                }
                free(hashtable.table);
                hashtable.currentTableSize = tableSize;
                hashtable.table = (struct Node_hash **)calloc(tableSize, sizeof(struct Node_hash *));
                if (hashtable.table == NULL)
                {
                    exit(EXIT_FAILURE);
                }
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
                while (fscanf(f, "%s", input) != EOF)
                {
                    insert_into_table(&hashtable, input);
                }
                fclose(f);
                break;
            case 6:
                printf("Введите слово для поиска в хеш-таблице: ");
                if (scanf("%s", input) != 1)
                {
                    printf("Некорректная строка\n");
                    break;
                }
                int cnt = 0;
                struct Node_hash *searchResult = search_in_table(&hashtable, input, &cnt);
                if (searchResult != NULL)
                {
                    printf("Слово найдено в хеш-таблице: %s\n", searchResult->word);
                }
                else
                {
                    printf("Слово не найдено в хеш-таблице\n");
                }
                break;

           case 7:
                if (hashtable.table != NULL)
                {
                    display_table(&hashtable);
                }
                else
                {
                    printf("Хеш-таблица не существует. Загрузите таблицу перед выводом.\n");
                }
                break;
            case 8:
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
            case 9:
                if (hashtable.table != NULL)
                {
                    measure_search_and_restructure_efficiency(&hashtable, "meow");
                }
                else
                {
                    printf("Хеш-таблица не существует. Загрузите таблицу перед сравнением.\n");
                }
                break;

            default:
                printf("Некорректное значение ввода\n");
                break;
            }
        }
    }

    for (int i = 0; i < hashtable.currentTableSize; i++)
    {
        struct Node_hash *current = hashtable.table[i];
        while (current != NULL)
        {
            struct Node_hash *next = current->next;
            free(current);
            current = next;
        }
    }
    free(hashtable.table);
    return 0;
}
