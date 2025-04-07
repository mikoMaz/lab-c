#ifndef BST_H
#define BST_H

typedef struct bst {
    int key;
    struct bst* left;
    struct bst* right;
} bst;

bst* bst_search(bst* node, int key);
bst* bst_insert(bst* node, int value);
void bst_free(bst* node);
int bst_depth(bst* node);
void bst_print(bst* node);

#endif
