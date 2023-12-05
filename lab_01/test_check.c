#include <stdio.h>
#include <stdbool.h>
#include "float.h"
#include "errs.h"

bool testInputFloat() {
    struct my_float floatStruct;
    char input1[] = "1.5E+5";
    char input2[] = "-2.7E-3";
    char input3[] = "4";
    char input4[] = "abc";
    char input5[] = "0.9999999999999999999999999999999999999999999999999999999999999999999";
    char input6[] = " ";
    char input7[] = "1.5E+";
    char input8[] = "1.5E";
    char input9[] = "E321+5";
    char input10[] = "1.e+1";
    char input11[] = "1.4E+1234567";
    char input12[] = "HELLo12";
    char input13[] = "1.5E+-9";

    int rc = input_float(input1, &floatStruct, MAX_FIRST_MANTISS_SIZE, MAX_ORDER_SIZE);
    if (rc != ERR_OK) {
        printf("Test 1 failed\n");
        return false;
    }

    rc = input_float(input2, &floatStruct, MAX_FIRST_MANTISS_SIZE, MAX_ORDER_SIZE);
    if (rc != ERR_OK) {
        printf("Test 2 failed\n");
        return false;
    }

    rc = input_float(input3, &floatStruct, MAX_FIRST_MANTISS_SIZE, MAX_ORDER_SIZE);
    if (rc != ERR_OK) {
        printf("Test 3 failed\n");
        return false;
    }

    rc = input_float(input4, &floatStruct, MAX_FIRST_MANTISS_SIZE, MAX_ORDER_SIZE);
    if (rc != ERR_RANGE) {
        printf("Test 4 failed\n");
        return false;
    }

    rc = input_float(input5, &floatStruct, MAX_FIRST_MANTISS_SIZE, MAX_ORDER_SIZE);
    if (rc != ERR_MANTISS_SIZE) {
        printf("Test 5 failed\n");
        return false;
    }

    rc = input_float(input6, &floatStruct, MAX_FIRST_MANTISS_SIZE, MAX_ORDER_SIZE);
    if (rc != ERR_RANGE) {
        printf("Test 6 failed\n");
        return false;
    }

    rc = input_float(input7, &floatStruct, MAX_FIRST_MANTISS_SIZE, MAX_ORDER_SIZE);
    if (rc != ERR_RANGE) {
        printf("Test 7 failed\n");
        return false;
    }

    rc = input_float(input8, &floatStruct, MAX_FIRST_MANTISS_SIZE, MAX_ORDER_SIZE);
    if (rc != ERR_RANGE) {
        printf("Test 8 failed\n");
        return false;
    }

    rc = input_float(input9, &floatStruct, MAX_FIRST_MANTISS_SIZE, MAX_ORDER_SIZE);
    if (rc != ERR_RANGE) {
        printf("Test 9 failed\n");
        return false;
    }

    rc = input_float(input10, &floatStruct, MAX_FIRST_MANTISS_SIZE, MAX_ORDER_SIZE);
    if (rc != ERR_RANGE) {
        printf("Test 10 failed\n");
        return false;
    }

    rc = input_float(input11, &floatStruct, MAX_FIRST_MANTISS_SIZE, MAX_ORDER_SIZE);
    if (rc != ERR_MANTISS_SIZE) {
        printf("Test 11 failed\n");
        return false;
    }

    rc = input_float(input12, &floatStruct, MAX_FIRST_MANTISS_SIZE, MAX_ORDER_SIZE);
    if (rc != ERR_RANGE) {
        printf("Test 12 failed\n");
        return false;
    }

    rc = input_float(input13, &floatStruct, MAX_FIRST_MANTISS_SIZE, MAX_ORDER_SIZE);
    if (rc != ERR_RANGE) {
        printf("Test 13 failed\n");
        return false;
    }

    printf("Все тесты пройдены\n");
    return true;
}