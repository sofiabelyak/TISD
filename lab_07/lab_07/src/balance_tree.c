#include "balance_tree.h"
#include <stdlib.h>


int height(Node *node) {
    if (node == NULL)
        return 0;

    int left_height = height(node->left);
    int right_height = height(node->right);

    return 1 + ((left_height > right_height) ? left_height : right_height);
}


int balance_factor(Node *node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}


Node *rotate_right(Node *y) {
    if (y == NULL || y->left == NULL)
        return y;

    Node *x = y->left;
    Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    return x;
}

Node *rotate_left(Node *x) {
    if (x == NULL || x->right == NULL)
        return x;

    Node *y = x->right;
    Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    return y;
}



Node *balance_tree(Node *root) {
    if (root == NULL)
        return NULL;

    int balance = balance_factor(root);
    if (balance > 1) {
        if (balance_factor(root->left) < 0) {
            root->left = rotate_left(root->left);
        }
        return rotate_right(root);
    }
    if (balance < -1)
    {
        if (balance_factor(root->right) > 0) {
            root->right = rotate_right(root->right);
        }
        return rotate_left(root);
    }
    return root;
}