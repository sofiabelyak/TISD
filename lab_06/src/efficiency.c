#include "efficiency.h"
#include "tree.h"
#include <time.h>

#define BILLION 1000000000

void words_for_letter_file(FILE *f, char letter)
{
    int cnt = 0;
    char input[100];
    while (fscanf(f, "%s", input) != EOF)
        if (input[0] == letter)
            cnt++;
}

void start_tests(FILE *f)
{
    size_t cnt = 0;
    int64_t av1, av2;
    char input[100];
    while (fscanf(f, "%s", input) != EOF)
        cnt++;
    rewind(f);

    printf("Количество слов: %lu\n\n", cnt);
    cnt = 0;

    int64_t sum_simple, sum = 0;
    struct Node *root = NULL;
    struct timespec start, stop;
    int count = 1000;
    printf("| Реализация | Время (нс) |\n");
    printf("|------------|------------|\n");

    for (int i = 0; i < count; i++)
    {
        clock_gettime(CLOCK_MONOTONIC, &start);
        words_for_letter_file(f, 'a');
        clock_gettime(CLOCK_MONOTONIC, &stop);
        rewind(f);
        sum_simple = BILLION * (stop.tv_sec - start.tv_sec) + (stop.tv_nsec - start.tv_nsec);
        sum += sum_simple;
    }
    av1 = sum / count;
    printf("| Файл       | %-10" PRId64 " |\n", av1);

    sum = 0;
    for (int i = 0; i < count; i++)
    {
        clock_gettime(CLOCK_MONOTONIC, &start);
        set_colour_for_letter(root, 'a', &cnt);
        clock_gettime(CLOCK_MONOTONIC, &stop);
        free_tree(root);
        root = NULL;
        cnt = 0;
        while (fscanf(f, "%s", input) != EOF)
            root = insert_node(root, input);
        rewind(f);
        sum_simple = BILLION * (stop.tv_sec - start.tv_sec) + (stop.tv_nsec - start.tv_nsec);
        sum += sum_simple;
    }
    av2 = sum / count;
    printf("| Дерево     | %-10" PRId64 " |\n", av2);

    printf("\nРазность производительности = %.2lf нс\n", fabs(av1 - av2));
    if (av1 > av2)
        printf("Реализация с помощью файла дольше на %lf %%\n", fabs(100 - (100 * av1 / av2)));
    else if (av1 < av2)
        printf("Реализация с помощью дерева дольше на %lf %%\n", fabs(100 - (100 * av2 / av1)));
    printf("\n");
}
