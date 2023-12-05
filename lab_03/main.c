#include "multiply_matrix.h"
#include "input_matrix.h"
#include "print.h"
#include "errors.h"
#include "read_matrix.h"
#include "cmp.h"
#define MAX_N 1001
int main(void)
{
    int rc = OK;
    int n, m, mb = 0;
    int *A = NULL, *JA = NULL, *IA = NULL;
    int *B = NULL, *IB = NULL, *JB = NULL;
    int *TValue = NULL, *TRowIndex = NULL, *TCol = NULL, *c = NULL;
    int choose = 1, flag = 0;
    printf("Цель программы: реализовать алгоритмы обработки разреженных матриц, сравнить\n");
    printf("эффективность использования этих алгоритмов со стандартными алгоритмами обработки матриц\n");
    printf("при различном процентном заполнении матриц ненулевыми значениями и при различных размерах матриц.\n");
    while ((choose > 0 && choose < 5) && choose != 0) 
    {
        printf("Меню:\n");
        printf("_____________________________________________\n");
        printf("_____________________________________________\n");

        printf("| 1. Умножить разреженную матрицу на вектор |\n");
        printf("|   1. Ввести разреженную матрицу вручную   |\n");
        printf("|   2. Ввести разреженную матрицу с файла   |\n");
        printf("| 2. Умножить полную матрицу на вектор      |\n");
        printf("|   1. Ввести матрицу вручную               |\n");
        printf("|   2. Ввести матрицу с файла               |\n");
        printf("| 3. Вывести матрицу                        |\n");
        printf("| 4. Сравнить алгоритмы матриц              |\n");
        printf("| 0. Выход из программы                     |\n");
        printf("–––––––––––––––––––––––––––––––––––––––––––––\n");

        if (scanf("%d", &choose) != 1) 
        {
            error_print(ERR_IO);
            return ERR_IO;
        }
        if (choose == 1)
        {
             printf("Разреженная матрица хранится в форме 3-х объектов: \n");
            printf("вектор A содержит значения ненулевых элементов;\n");
            printf("вектор JA содержит номера столбцов для элементов вектора A;\n");
            printf("вектор IA, в элементе Nk которого находится номер компонент в A и JA, с которых начинается описание строки Nk матрицы A.\n");
            int tmp = 0, nv = 0;
            int *vec = NULL;
            int a_len_i, a_elem_count;
            printf("Введите 1 если хотите ввести матрицу вручную, 2 - прочитать из файла\n");
            if (scanf("%d", &tmp)!= 1)
            {
                error_print(ERR_IO);
                return ERR_IO;
            }
            if (tmp == 1)
            {
                printf("Введите матрицу А:\n");
                rc  = input_matrix(&n, &m, &A, &JA, &IA, &a_len_i, &a_elem_count);
                if (rc != OK)
                {
                    error_print(rc);
                    return rc;
                }
                rc = input_vector(&vec, &nv);
                if (rc != OK)
                {
                    error_print(rc);
                    return rc;
                }
            }
            else if (tmp == 2)
            {
                FILE *f1;
                f1 = fopen("matrix_a.txt", "r");
                if (f1 == NULL)
                {
                    error_print(ERR_FILE);
                    return ERR_FILE;
                }
                rc =  read_matrix_from_file(f1, &A, &IA, &JA, &n, &m, &a_len_i, &a_elem_count);
                if (rc != OK)
                {
                    error_print(rc);
                    return rc;
                }
                rc = input_vector(&vec, &nv);
                if (rc != OK)
                {
                    error_print(rc);
                    return rc;
                }
                fclose(f1);
            }
            if (m != nv)
                printf("Невозможно перемножить\n");
            else
            {
                flag = 1;
                multiply_sparse_matrix_to_vector(A, IA, JA, vec, n, nv, &c);
                printf("Умножение выполнено!\n");
            }
            free(vec);
        }
        else if (choose == 2)
        {
            int tmp = 0, nv = 0;
            int *vec = NULL;
            printf("Введите 1 если хотите ввести матрицу вручную, 2 - прочитать из файла\n");
            if (scanf("%d", &tmp)!= 1)
            {
                error_print(ERR_IO);
                return ERR_IO;
            }
            if (tmp == 1)
            {
                printf("Введите матрицу А:\n");
                rc = full_matrix(&A, &IA, &JA, &n, &m);
                if (rc != OK)
                {
                    error_print(rc);
                    return rc;
                }
                rc = input_vector(&vec, &nv);

                if (rc != OK)
                {
                    error_print(rc);
                    return rc;
                }
            }
            else if (tmp == 2)
            {
                FILE *f1;
                f1 = fopen("./matrix_a.txt", "r");
                if (f1 == NULL)
                {
                    error_print(ERR_FILE);
                    return ERR_FILE;
                }
                rc = read_full_matrix_from_file(f1, &A, &IA, &JA, &n, &m);
                if (rc != OK)
                {
                    error_print(rc);
                    return rc;
                }
                rc = input_vector(&vec, &nv);
                if (rc != OK)
                {
                    error_print(rc);
                    return rc;
                }
                fclose(f1);
            }
            if (m != nv)
                printf("Невозможно перемножить\n");
            else
            {
                multiply_matrix_to_vector(A, IA, JA, vec, n, m, nv, &c);
                printf("Умножение выполнено!\n");
                flag = 1;
            }
            free(vec);
        }
        else if (choose == 3)
        {
            if (flag == 0)
                printf("Введите матрицу\n");
            else
            {
                if (n > MAX_N || m > MAX_N)
                    printf("Матрица слишком большая.\n");
                else
                {
                    if (flag == 1)
                    {
                        print_matrix_to_vector(c, n);
                    }
                    else if (flag == 2)
                    {
                       print_matrix(c, n, mb);
                    }
                }
            }
        }
        else if (choose == 4)
        {
            compare_matrix_operations();
        }
    }
    free(A);
    free(JA);
    free(IA);
    free(B);
    free(IB);
    free(JB);
    free(TValue);
    free(TCol);
    free(TRowIndex);
    free(c);
    return rc;
}
