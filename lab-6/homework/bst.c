#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

bst* bst_search(bst* node, int key) {
    while (node != NULL) {
        if (key == node->key) {
            return node;
        }
        else if (key < node->key) {
            node = node->left;
        }
        else {
            node = node->right;
        }
    }
    return NULL;
}

bst* bst_insert(bst* node, int value) {
    if (node == NULL) {
        bst* new_node = (bst*)malloc(sizeof(bst));
        new_node->key = value;
        new_node->left = NULL;
        new_node->right = NULL;
        return new_node;
    }

    if (value < node->key) {
        node->left = bst_insert(node->left, value);
    }
    else if (value > node->key) {
        node->right = bst_insert(node->right, value);
    }
    return node;
}

void bst_free(bst* node) {
    if (node == NULL) {
        return;
    }
    bst_free(node->left);
    bst_free(node->right);
    free(node);
}

int bst_depth(bst* node) {
    if (node == NULL) {
        return 0;
    }
    
    int left_depth = bst_depth(node->left);
    int right_depth = bst_depth(node->right);
    
    return (left_depth > right_depth ? left_depth : right_depth) + 1;
}

void bst_print(bst* node) {
    if (node != NULL) {
        bst_print(node->left);
        printf("%d ", node->key);
        bst_print(node->right);
    }
}
