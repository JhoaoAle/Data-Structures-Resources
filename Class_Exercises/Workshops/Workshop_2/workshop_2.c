#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N 10000
#define SEARCHES 25
#define ITER 10


char *random_name() {
    int len = rand() % 8 + 3;
    char *name = (char *)malloc(len + 1);
    for (int i = 0; i < len; i++) {
        name[i] = 'a' + rand() % 26;
    }
    name[len] = '\0';
    return name;
}

int cmpstr(const void *a, const void *b) {
    return strcmp(*(char **)a, *(char **)b);
}


typedef struct BST {
    char *key;
    struct BST *left, *right;
} BST;

BST* bst_insert(BST* root, char* key) {
    BST *parent = NULL, *curr = root;

    while (curr) {
        parent = curr;
        if (strcmp(key, curr->key) < 0)
            curr = curr->left;
        else
            curr = curr->right;
    }

    BST* node = malloc(sizeof(BST));
    node->key = key;
    node->left = node->right = NULL;

    if (!parent) return node;

    if (strcmp(key, parent->key) < 0)
        parent->left = node;
    else
        parent->right = node;

    return root;
}

int bst_search(BST* root, char* key) {
    while (root) {
        int c = strcmp(key, root->key);
        if (c == 0) return 1;
        if (c < 0) root = root->left;
        else root = root->right;
    }
    return 0;
}

void bst_free(BST *root) {
    if (!root) return;
    bst_free(root->left);
    bst_free(root->right);
    free(root);
}


typedef struct AVL {
    char *key;
    struct AVL *left, *right;
    int height;
} AVL;

int height(AVL *n) { return n ? n->height : 0; }
int max(int a, int b) { return a > b ? a : b; }

AVL* newAVL(char* key) {
    AVL* n = malloc(sizeof(AVL));
    n->key = key;
    n->left = n->right = NULL;
    n->height = 1;
    return n;
}

AVL* rightRotate(AVL* y) {
    AVL* x = y->left;
    y->left = x->right;
    x->right = y;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

AVL* leftRotate(AVL* x) {
    AVL* y = x->right;
    x->right = y->left;
    y->left = x;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

int getBalance(AVL* n) {
    return n ? height(n->left) - height(n->right) : 0;
}

AVL* avl_insert(AVL* node, char* key) {
    if (!node) return newAVL(key);

    if (strcmp(key, node->key) < 0)
        node->left = avl_insert(node->left, key);
    else
        node->right = avl_insert(node->right, key);

    node->height = 1 + max(height(node->left), height(node->right));
    int balance = getBalance(node);

    if (balance > 1 && strcmp(key, node->left->key) < 0)
        return rightRotate(node);

    if (balance < -1 && strcmp(key, node->right->key) > 0)
        return leftRotate(node);

    if (balance > 1 && strcmp(key, node->left->key) > 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && strcmp(key, node->right->key) < 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

int avl_search(AVL* root, char* key) {
    if (!root) return 0;
    int c = strcmp(key, root->key);
    if (c == 0) return 1;
    if (c < 0) return avl_search(root->left, key);
    return avl_search(root->right, key);
}

void avl_free(AVL *root) {
    if (!root) return;
    avl_free(root->left);
    avl_free(root->right);
    free(root);
}


typedef enum { RED, BLACK } Color;

typedef struct RBT {
    char *key;
    Color color;
    struct RBT *left, *right, *parent;
} RBT;

RBT* newRBT(char* key) {
    RBT* n = malloc(sizeof(RBT));
    n->key = key;
    n->color = RED;
    n->left = n->right = n->parent = NULL;
    return n;
}

void leftRotateRBT(RBT **root, RBT *x) {
    RBT *y = x->right;
    x->right = y->left;
    if (y->left) y->left->parent = x;
    y->parent = x->parent;

    if (!x->parent) *root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;

    y->left = x;
    x->parent = y;
}

void rightRotateRBT(RBT **root, RBT *y) {
    RBT *x = y->left;
    y->left = x->right;
    if (x->right) x->right->parent = y;
    x->parent = y->parent;

    if (!y->parent) *root = x;
    else if (y == y->parent->left) y->parent->left = x;
    else y->parent->right = x;

    x->right = y;
    y->parent = x;
}

void fixInsert(RBT **root, RBT *z) {
    while (z->parent && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            RBT *y = z->parent->parent->right;

            if (y && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotateRBT(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotateRBT(root, z->parent->parent);
            }
        } else {
            RBT *y = z->parent->parent->left;

            if (y && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotateRBT(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotateRBT(root, z->parent->parent);
            }
        }
    }
    (*root)->color = BLACK;
}

void rbt_insert(RBT **root, char* key) {
    RBT *z = newRBT(key);
    RBT *y = NULL, *x = *root;

    while (x) {
        y = x;
        if (strcmp(z->key, x->key) < 0) x = x->left;
        else x = x->right;
    }

    z->parent = y;
    if (!y) *root = z;
    else if (strcmp(z->key, y->key) < 0) y->left = z;
    else y->right = z;

    fixInsert(root, z);
}

int rbt_search(RBT* root, char* key) {
    if (!root) return 0;
    int c = strcmp(key, root->key);
    if (c == 0) return 1;
    if (c < 0) return rbt_search(root->left, key);
    return rbt_search(root->right, key);
}

void rbt_free(RBT *root) {
    if (!root) return;
    rbt_free(root->left);
    rbt_free(root->right);
    free(root);
}


void run_test(char **names) {
    BST *bst = NULL;
    AVL *avl = NULL;
    RBT *rbt = NULL;

    clock_t start, end;

    start = clock();
    for (int i = 0; i < N; i++) bst = bst_insert(bst, names[i]);
    end = clock();
    double bst_insert_t = (double)(end - start)/CLOCKS_PER_SEC;

    start = clock();
    for (int i = 0; i < N; i++) avl = avl_insert(avl, names[i]);
    end = clock();
    double avl_insert_t = (double)(end - start)/CLOCKS_PER_SEC;

    start = clock();
    for (int i = 0; i < N; i++) rbt_insert(&rbt, names[i]);
    end = clock();
    double rbt_insert_t = (double)(end - start)/CLOCKS_PER_SEC;

    start = clock();
    for (int i = 0; i < SEARCHES; i++)
        bst_search(bst, names[rand()%N]);
    end = clock();
    double bst_search_t = (double)(end - start)/CLOCKS_PER_SEC;

    start = clock();
    for (int i = 0; i < SEARCHES; i++)
        avl_search(avl, names[rand()%N]);
    end = clock();
    double avl_search_t = (double)(end - start)/CLOCKS_PER_SEC;

    start = clock();
    for (int i = 0; i < SEARCHES; i++)
        rbt_search(rbt, names[rand()%N]);
    end = clock();
    double rbt_search_t = (double)(end - start)/CLOCKS_PER_SEC;

    printf("\nBST  -> Insert: %.4f | Search: %.6f\n", bst_insert_t, bst_search_t);
    printf("AVL  -> Insert: %.4f | Search: %.6f\n", avl_insert_t, avl_search_t);
    printf("RBT  -> Insert: %.4f | Search: %.6f\n", rbt_insert_t, rbt_search_t);

    bst_free(bst);
    avl_free(avl);
    rbt_free(rbt);
}



int main() {
    srand(time(NULL));

    for (int it = 0; it < ITER; it++) {

        char **names = malloc(N * sizeof(char*));

        for (int i = 0; i < N; i++)
            names[i] = random_name();

        printf("\nITERATION %d (Random Order)\n", it+1);
        run_test(names);

        qsort(names, N, sizeof(char*), cmpstr);
        printf("\nITERATION %d (Sorted ASC)\n", it+1);
        run_test(names);

        for (int i = 0; i < N/2; i++) {
            char* tmp = names[i];
            names[i] = names[N-i-1];
            names[N-i-1] = tmp;
        }

        printf("\nITERATION %d (Sorted DESC)\n", it+1);
        run_test(names);

        // FREE STRINGS (IMPORTANT)
        for (int i = 0; i < N; i++)
            free(names[i]);
        free(names);
    }

    return 0;
}