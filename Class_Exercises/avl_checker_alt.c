#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Node structure
typedef struct Node {
    int key;
    struct Node *left, *right;
} Node;

// Create node
Node* newNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->left = node->right = NULL;
    return node;
}

// BST insert
Node* insert(Node* root, int key) {
    if (root == NULL) return newNode(key);

    if (key < root->key)
        root->left = insert(root->left, key);
    else
        root->right = insert(root->right, key);

    return root;
}

// Height + AVL check
int heightAndCheck(Node* root, bool *isBalanced) {
    if (root == NULL) return -1;

    int leftH = heightAndCheck(root->left, isBalanced);
    int rightH = heightAndCheck(root->right, isBalanced);

    int bf = leftH - rightH;

    if (bf < -1 || bf > 1)
        *isBalanced = false;

    return (leftH > rightH ? leftH : rightH) + 1;
}

int main() {
    int N, key;
    scanf("%d", &N);

    Node* root = NULL;

    for (int i = 0; i < N; i++) {
        scanf("%d", &key);
        root = insert(root, key);
    }

    bool isBalanced = true;
    heightAndCheck(root, &isBalanced);

    if (isBalanced)
        printf("Yes\n");
    else
        printf("No\n");

    return 0;
}