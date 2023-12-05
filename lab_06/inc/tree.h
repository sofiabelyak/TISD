#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Node
{
    char *data;
    struct Node *left;
    struct Node *right;
    bool colour;
} Node;

Node *create_node(char *data);

Node *insert_node(Node *root, char *data);

Node *find_node(Node *root, char *data);

Node *find_min(Node *node);

Node *delete_node(Node *root, char *data);

void free_tree(Node *root);

void set_colour_for_letter(Node *root, char letter, size_t *cnt);

void draw_tree(Node *root, size_t n, char dir);

void draw_line(struct Node* root);

#endif
