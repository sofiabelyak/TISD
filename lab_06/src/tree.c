#include "tree.h"

Node *create_node(char *data)
{
    Node *new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL)
        return NULL;
    new_node->data = strdup(data);
    new_node->left = new_node->right = NULL;
    new_node->colour = false;
    return new_node;
}

Node *insert_node(Node *root, char *data)
{
    if (root == NULL)
        return create_node(data);

    int cmp = strcmp(data, root->data);
    if (cmp < 0)
        root->left = insert_node(root->left, data);
    else if (cmp > 0)
        root->right = insert_node(root->right, data);

    return root;
}

Node *find_node(Node *root, char *data)
{
    if (root == NULL || strcmp(root->data, data) == 0)
        return root;

    if (strcmp(data, root->data) < 0)
        return find_node(root->left, data);
    else
        return find_node(root->right, data);
}

Node *find_min(Node *node)
{
    while (node->left != NULL)
        node = node->left;

    return node;
}

Node *delete_node(Node *root, char *data)
{
    if (root == NULL) {
        return root;
    }

    int cmp = strcmp(data, root->data);
    if (cmp < 0) {
        root->left = delete_node(root->left, data);
    } else if (cmp > 0) {
        root->right = delete_node(root->right, data);
    } else {
        if (root->left == NULL) {
            Node *temp = root->right;
            free(root->data);
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node *temp = root->left;
            free(root->data);
            free(root);
            return temp;
        }

        Node *temp = find_min(root->right);
        free(root->data);
        root->data = strdup(temp->data);
        root->right = delete_node(root->right, temp->data);
    }

    return root;
}

void free_tree(Node *root)
{
    if (root != NULL) {
        free_tree(root->left);
        free_tree(root->right);
        free(root->data);
        free(root);
        root = NULL;
    }
}

void set_colour_for_letter(Node *root, char letter, size_t *cnt)
{
    if (root == NULL)
        return;

    while(root && root->data[0] != letter)
    {
        if (root->data[0] > letter)
        {
            if (root->left)
                root = root->left;
            else
                return;
        }
        else if (root->data[0] < letter)
        {
            if (root->right)
                root = root->right;
            else
                return;
        }
    }
    if (root->data[0] == letter)
    {
        root->colour = true;
        (*cnt)++;
        set_colour_for_letter(root->right, letter, cnt);
        set_colour_for_letter(root->left, letter, cnt);
    }
}

void draw_tree(Node *root, size_t n, char dir)
{
    if (root)
    {
        draw_tree(root->right, n + 4, '/');
        for (size_t i = 0; i < n; i++)
        {
            if (i % 4 == 0)
                printf("\x1b[90m|\x1b[0m");
            else
                printf(" ");
        }
        if (root->colour)
            printf("%c\033[0;35m%s\033[0;37m\n", dir, root->data);
        else
            printf("%c%s\n", dir, root->data);
        draw_tree(root->left, n + 4, '\\');
    }
}

void draw_line(struct Node* root)
{
    if (root != NULL)
    {
        draw_line(root->left);
        if (root->colour)
            printf("\033[0;35m%s\033[0;37m ", root->data);
        else
            printf("%s ", root->data);
        draw_line(root->right);
    }
}
