#include "hash_table.h"

unsigned int hash_function(const char *word)
{
    unsigned int hash = 0;
    for (int i = 0; word[i] != '\0'; i++)
    {
        hash = hash * 31 + word[i];
    }
    return hash;
}

float load_factor(const struct HashTable *hashtable)
{
    int count = 0;
    for (int i = 0; i < hashtable->currentTableSize; i++)
    {
        struct Node_hash *current = hashtable->table[i];
        while (current != NULL)
        {
            count++;
            current = current->next;
        }
    }

    return (float)count / hashtable->currentTableSize;
}

void restructure_table(struct HashTable *hashtable, int new_size)
{
    struct Node_hash **new_table = (struct Node_hash **)calloc(new_size, sizeof(struct Node_hash *));
    if (new_table == NULL)
    {
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < hashtable->currentTableSize; i++)
    {
        struct Node_hash *current = hashtable->table[i];
        while (current != NULL)
        {
            struct Node_hash *next = current->next;
            unsigned int new_index = hash_function(current->word) % new_size;
            while (new_table[new_index] != NULL)
            {
                new_index = (new_index + 1) % new_size;
            }

            current->next = NULL;
            new_table[new_index] = current;

            current = next;
        }
    }

    free(hashtable->table);

    hashtable->table = new_table;
    hashtable->currentTableSize = new_size;

    printf("Хеш-таблица была реструктурирована. Новый размер: %d\n", new_size);
}



void insert_into_table(struct HashTable *hashtable, const char *word)
{
    unsigned int index = hash_function(word) % hashtable->currentTableSize;
    int originalIndex = index;
    if (hashtable->table[index] == NULL)
    {
        struct Node_hash *newNode = (struct Node_hash *)malloc(sizeof(struct Node_hash));
        if (newNode == NULL)
        {
            exit(EXIT_FAILURE);
        }
        strcpy(newNode->word, word);
        newNode->occupied = 1;
        newNode->next = NULL;

        hashtable->table[index] = newNode;

        if (load_factor(hashtable) > 0.75)
        {
            int new_size = hashtable->currentTableSize * GROWTH_FACTOR;
            new_size = (new_size < hashtable->currentTableSize + 1) ? new_size + 1 : new_size;
            restructure_table(hashtable, new_size);
        }

        return;
    }
    while (hashtable->table[index] != NULL && hashtable->table[index]->occupied)
    {
        index = (index + 1) % hashtable->currentTableSize;
        if (index == originalIndex)
        {
            return;
        }
    }

    struct Node_hash *newNode = (struct Node_hash *)malloc(sizeof(struct Node_hash));
    if (newNode == NULL)
    {
        exit(EXIT_FAILURE);
    }
    strcpy(newNode->word, word);
    newNode->occupied = 1;
    newNode->next = NULL;

    hashtable->table[index] = newNode;

    if (load_factor(hashtable) > 0.75)
    {
        int new_size = hashtable->currentTableSize * GROWTH_FACTOR;
        new_size = (new_size < hashtable->currentTableSize + 1) ? new_size + 1 : new_size;
        restructure_table(hashtable, new_size);
    }
}


void display_table(const struct HashTable *hashtable)
{
    printf("Hash Table:\n");
    for (int i = 0; i < hashtable->currentTableSize; i++)
    {
        printf("%d: ", i);
        struct Node_hash *current = hashtable->table[i];
        while (current != NULL)
        {
            printf("%s ", current->word);
            current = current->next;
        }
        printf("\n");
    }
}

struct Node_hash *search_in_table(const struct HashTable *hashtable, const char *word, int *comparisons)
{
    unsigned int index = hash_function(word) % hashtable->currentTableSize;
    int originalIndex = index;

    *comparisons = 0;

    while (hashtable->table[index] != NULL && hashtable->table[index]->occupied)
    {
        (*comparisons)++;
        if (strcmp(hashtable->table[index]->word, word) == 0)
        {
            if (*comparisons > 3)
            {
                printf("Предупреждение: Количество сравнений при поиске элемента больше 3\n");
            }
            return hashtable->table[index];
        }

        index = (index + 1) % hashtable->currentTableSize;

        if (index == originalIndex)
        {
            break;
        }
    }

    if (*comparisons > 3)
    {
        printf("Предупреждение: Количество сравнений при поиске элемента больше 3\n");
    }

    return NULL;
}

