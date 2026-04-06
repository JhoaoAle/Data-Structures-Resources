#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    struct Node* left;
    struct Node* right;
    int height;
} Node;

int height(Node* node){
    if (node == NULL) return 0;
    return node->height;
}

int max(int a, int b){
    return (a > b) ? a : b;
}

int getBalance(Node* node){
    if (node == NULL) return 0;
    return height(node->left) - height(node->right);
}

Node* create_node(int value){
    Node* new_node = (Node*)malloc(sizeof(Node));

    new_node->key = value;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->height = 1;

    return new_node;
}

Node* rightRotate(Node* y){
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    x->height = max(height(x->left),height(x->right)) + 1;
    y->height = max(height(y->left),height(y->right)) + 1;

    return x;
}

Node* leftRotate(Node* x){
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left),height(x->right)) + 1;
    y->height = max(height(y->left),height(y->right)) + 1;

    return y;
}

Node* insert_node(Node* root, int key){
    if(root == NULL) return create_node(key);

    //This is regular BST insertion
    if(key < root->key) root->left = insert_node(root->left, key);
    else if(key > root->key) root->right = insert_node(root->right, key);
    else return root;

    // Now to update height
    root->height = max(height(root->left),height(root->right)) + 1;

    int balance = getBalance(root);

    if (balance > 1 && key < root->left->key) return rightRotate(root);
    if (balance > 1 && key > root->left->key){
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && key > root->right->key) return  leftRotate(root);
    if (balance < -1 && key < root->right->key){
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}


