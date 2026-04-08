#include <stdio.h>
#include <stdlib.h>

// Node structure
typedef struct Node {
    int key;
    struct Node *left, *right;
} Node;

// Create a new node
Node* newNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->left = node->right = NULL;
    return node;
}

// Insert into BST
Node* insert(Node* root, int key) {
    if (root == NULL) return newNode(key);

    if (key < root->key)
        root->left = insert(root->left, key);
    else
        root->right = insert(root->right, key);

    return root;
}

// Get height of tree
int height(Node* root) {
    if (root == NULL) return -1; // height of empty tree

    int leftH = height(root->left);
    int rightH = height(root->right);

    return (leftH > rightH ? leftH : rightH) + 1;
}

// Check AVL condition
int isAVL(Node* root) {
    if (root == NULL) return 1;

    int leftH = height(root->left);
    int rightH = height(root->right);

    int bf = leftH - rightH;

    if (bf < -1 || bf > 1)
        return 0;

    return isAVL(root->left) && isAVL(root->right);
}

int main() {
    int N, key;
    scanf("%d", &N);

    Node* root = NULL;

    for (int i = 0; i < N; i++) {
        scanf("%d", &key);
        root = insert(root, key);
    }

    if (isAVL(root))
        printf("Yes\n");
    else
        printf("No\n");

    return 0;
}