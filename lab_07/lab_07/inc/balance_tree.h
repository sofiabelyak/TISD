#ifndef BALANCE_TREE_H
#define BALANCE_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "tree.h"

/**
 * @brief Вычисляет высоту узла в AVL-дереве.
 * 
 * @param node Указатель на узел.
 * @return int Высота узла.
 */
int height(struct Node *node);

/**
 * @brief Вычисляет коэффициент баланса для узла в AVL-дереве.
 * 
 * @param node Указатель на узел.
 * @return int Коэффициент баланса.
 */
int balance_factor(struct Node *node);

/**
 * @brief Выполняет правый поворот в AVL-дереве.
 * 
 * @param y Указатель на узел, вокруг которого выполняется поворот.
 * @return struct Node* Указатель на новый корень поддерева.
 */
struct Node *rotate_right(struct Node *y);

/**
 * @brief Выполняет левый поворот в AVL-дереве.
 * 
 * @param x Указатель на узел, вокруг которого выполняется поворот.
 * @return struct Node* Указатель на новый корень поддерева.
 */
struct Node *rotate_left(struct Node *x);

/**
 * @brief Балансирует AVL-дерево, выполняя необходимые повороты.
 * 
 * @param root Указатель на корень AVL-дерева.
 * @return struct Node* Указатель на новый корень AVL-дерева после балансировки.
 */
struct Node *balance_tree(struct Node *root);

#endif