#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct _Tree {
    void* key;
    struct _Tree *left;
    struct _Tree *right;
} Tree;

Tree* insert(Tree* t, void* data) {
    if ( t == NULL ) {
         t = malloc(sizeof(Tree));
         t->key = data;
         t->left = NULL;
         t->right = NULL;
         return t;
    }
    else if ( data >= t->key ) {
        t->right = insert(t->right, data);
    }
    else {
        t->left = insert(t->left, data);
    }
    return t;
}

void search(Tree* t, void* data) {
    if ( t == NULL ) {
        printf("false\n");
    }
    else if ( t->key == data ) {
        printf("true\n");
    }
    else if (t->key > data ) {
        search(t->left, data);
    }
    else {
        search(t->right, data);
    }
}

void delete(Tree* t) {
    if ( t != NULL ) {
        delete(t->left);
        delete(t->right);
        free(t);
    }
    else {
        return;
    }
}

void print_tree(Tree* t) {
    if ( t == NULL ) {
        return;
    }
    print_tree(t->left);
    printf("%p\n", t->key);
    print_tree(t->right);
}


int main() {
    Tree* t = NULL;
    int n = 1000;
    for(int i = 0; i < n; ++i) {
        long j = rand() % 1000;
        t = insert(t, (void*)j);
    }
    //print_tree(t);
    delete(t);
    return 0;
}

