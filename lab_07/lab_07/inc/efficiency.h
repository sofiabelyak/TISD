#ifndef EFF_H
#define EFF_H

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include <sys/time.h>
#include <inttypes.h>
#include "hash_table.h"
void start_tests(FILE *f);
void measure_search_and_restructure_efficiency(struct HashTable *hashtable, const char *searchWord);

#endif
