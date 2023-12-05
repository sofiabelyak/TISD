#include "efficiency.h"
#include "tree.h"
#include <time.h>
#include "balance_tree.h"
#include "hash_table.h"

#define BILLION 1000000000

// Функция для измерения объема памяти для дерева
size_t measure_memory_tree(Node *root)
{
    if (root == NULL) {
        return 0;
    }
    return sizeof(Node) + strlen(root->data) + measure_memory_tree(root->left) + measure_memory_tree(root->right);
}

// Функция для измерения объема памяти для хеш-таблицы
size_t measure_memory_hash(const struct HashTable *hashtable) {
    if (hashtable == NULL || hashtable->table == NULL) {
        return 0;
    }

    size_t memory = 0;

    for (int i = 0; i < hashtable->currentTableSize; i++) {
        struct Node_hash *current = hashtable->table[i];
        while (current != NULL) {
            memory += sizeof(struct Node_hash) + strlen(current->word);
            current = current->next;
        }
    }

    return memory;
}

Node* copy_tree_recursive(Node* original) {
    if (original == NULL) {
        return NULL;
    }

    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        exit(EXIT_FAILURE);
    }

    new_node->data = strdup(original->data);
    new_node->left = copy_tree_recursive(original->left);
    new_node->right = copy_tree_recursive(original->right);
    new_node->colour = original->colour;

    return new_node;
}

Node* copy_tree(Node* original) {
    return copy_tree_recursive(original);
}

void start_tests(FILE *f)
{
    int64_t av1, av2;
    char input[100];
    int comparisons_unbalanced, comparisons_balanced, comparisons_hash;
    size_t memory_unbalanced, memory_balanced, memory_hash;
    struct Node *root_unbalanced = NULL;
    while (fscanf(f, "%s", input) != EOF)
        root_unbalanced = insert_node(root_unbalanced, input);

    rewind(f);
    struct Node *root_balanced = copy_tree(root_unbalanced);
    root_balanced = balance_tree(root_balanced);
    int64_t sum_simple, sum = 0;
    struct timespec start, stop;
    int count = 100000;
    printf("| Реализация          | Время (нс) | Кол-во срав. | Память     |\n");
    printf("|---------------------|------------|--------------|------------|\n");
    comparisons_unbalanced = 0;
    // Выполняем поиск в несбалансированном дереве
    for (int i = 0; i < count; i++)
    {
        clock_gettime(CLOCK_MONOTONIC, &start);
        find_node(root_unbalanced, "meow", &comparisons_unbalanced);
        clock_gettime(CLOCK_MONOTONIC, &stop);
        rewind(f);
        // Замеряем время
        sum_simple = BILLION * (stop.tv_sec - start.tv_sec) + (stop.tv_nsec - start.tv_nsec);
        sum += sum_simple;
    }
    av1 = sum / count;
    memory_unbalanced = measure_memory_tree(root_unbalanced);
    printf("| Несбалансированное  | %-10" PRId64 " | %12d | %-10zu |\n", av1, comparisons_unbalanced / count, memory_unbalanced);

    free_tree(root_unbalanced);
    // Выполняем поиск в сбалансированном дереве
    sum = 0;
    comparisons_balanced = 0;
    for (int i = 0; i < count; i++)
    {
        clock_gettime(CLOCK_MONOTONIC, &start);
        find_node(root_balanced, "meow", &comparisons_balanced);
        clock_gettime(CLOCK_MONOTONIC, &stop);
        rewind(f);
        // Замеряем время
        sum_simple = BILLION * (stop.tv_sec - start.tv_sec) + (stop.tv_nsec - start.tv_nsec);
        sum += sum_simple;
    }
    av2 = sum / count;
    memory_balanced = measure_memory_tree(root_balanced);
    printf("| Сбалансированное    | %-10" PRId64 " | %12d | %-10zu |\n", av2, comparisons_balanced / count, memory_balanced);
    free_tree(root_balanced);

    int64_t av3, sum_hash = 0;
    struct HashTable hashtable;
    hashtable.currentTableSize = INITIAL_TABLE_SIZE;
    hashtable.table = (struct Node_hash **)calloc(INITIAL_TABLE_SIZE, sizeof(struct Node_hash *));
    if (hashtable.table == NULL)
    {
        exit(EXIT_FAILURE);
    }
    while (fscanf(f, "%s", input) != EOF)
        insert_into_table(&hashtable, input);
    rewind(f);
    comparisons_hash = 0;
    for (int i = 0; i < count; i++)
    {
        clock_gettime(CLOCK_MONOTONIC, &start);
        search_in_table(&hashtable, "meow", &comparisons_hash);
        clock_gettime(CLOCK_MONOTONIC, &stop);
        rewind(f);

        // Замеряем время
        int64_t sum_simple = BILLION * (stop.tv_sec - start.tv_sec) + (stop.tv_nsec - start.tv_nsec);
        sum_hash += sum_simple;
        rewind(f);
    }
    av3 = sum_hash / count;
    memory_hash = measure_memory_hash(&hashtable);
    printf("| Хеш-таблица         | %-10" PRId64 " | %12d | %-10zu |\n", av3, comparisons_hash, memory_hash);
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

    printf("\nРазность производительности:\n");
    printf("С несбалансированным деревом = %.2lf нс\n", fabs(av1 - av3));
    printf("С балансированным деревом    = %.2lf нс\n", fabs(av2 - av3));
    if (av1 > av3)
        printf("Хеш-таблица быстрее на %lf %% от несбалансированного дерева\n", fabs(100 - (100 * av3 / av1)));
    if (av2 > av3)
        printf("Хеш-таблица быстрее на %lf %% от балансированного дерева\n", fabs(100 * av3 / av2));
    printf("\n");
}

void measure_search_and_restructure_efficiency(struct HashTable *hashtable, const char *searchWord)
{
    int comparisons_search, comparisons_restructure;
    struct timespec start, stop;
    int count = 1000;
    // Измерение эффективности поиска в исходной таблице
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int i = 0; i < count; i++) {
        search_in_table(hashtable, searchWord, &comparisons_search);
    }
    clock_gettime(CLOCK_MONOTONIC, &stop);

    int64_t time_search = (BILLION * (stop.tv_sec - start.tv_sec) + (stop.tv_nsec - start.tv_nsec)) / count;

    restructure_table(hashtable, 150);
    
    // Измерение эффективности поиска в таблице после реструктуризации
    clock_gettime(CLOCK_MONOTONIC, &start);

    for (int i = 0; i < count; i++) 
    {
        search_in_table(hashtable, searchWord, &comparisons_restructure);
    }
    clock_gettime(CLOCK_MONOTONIC, &stop);

    int64_t time_search_restructured = (BILLION * (stop.tv_sec - start.tv_sec) + (stop.tv_nsec - start.tv_nsec)) / count ;

    // Вывод результатов
    printf("Исходная таблица: Время поиска - %" PRId64 " нс, Сравнения - %d\n", time_search, comparisons_search);
    printf("После реструктуризации: Время поиска - %" PRId64 " нс, Сравнения - %d\n", time_search_restructured, comparisons_restructure);
    printf("Эффективность реструктуризации: %lf%% ускорения в сравнении с исходной таблицей\n", (1.0 - (double)time_search_restructured / time_search) * 100);
}
