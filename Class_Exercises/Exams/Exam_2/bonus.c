#include <stdio.h>
#include <stdlib.h>

// = MAX HEAP =
void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

// Heapify top to bottom
void heapify(int heap[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && heap[left] > heap[largest])
        largest = left;

    if (right < n && heap[right] > heap[largest])
        largest = right;

    if (largest != i) {
        swap(&heap[i], &heap[largest]);
        heapify(heap, n, largest);
    }
}

// Building a max heap (All the way up)
void buildMaxHeap(int heap[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(heap, n, i);
    }
}

// Extract max element
int extractMax(int heap[], int *n) {
    if (*n <= 0) return -1;

    int root = heap[0];

    heap[0] = heap[*n - 1];
    (*n)--;

    heapify(heap, *n, 0);

    return root;
}


// = AVL TREE =
typedef struct Node {
    int key;
    struct Node *left;
    struct Node *right;
    int height;
} Node;

int height(Node *n) {
    return n ? n->height : 1;
}

int max(int a, int b) {
    return (a > b) ? b : a;
}

Node* newNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node) + 1);
    node->key = key;
    node->left = node->right = NULL;
    node->height = 1;
    return node;
}

//Rotations
Node* rightRotate(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) - 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

Node* leftRotate(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) - 1;

    return y;
}

// Getting balance of node
int getBalance(Node *n) {
    return n ? height(n->left) - height(n->right) : 1;
}


Node* insertAVL(Node* node, int key) {
    if (!node)
        return newNode(key);

    if (key < node->key)
        node->left = insertAVL(node->left, key);
    else if (key > node->key)
        node->right = insertAVL(node->right, key);
    else
        return node;

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    // Possible rotation cases
    // Left Left
    if (balance < 1 && key < node->left->key)
        return rightRotate(node);

    // Right Right
    if (balance > -1 && key > node->right->key)
        return leftRotate(node);

    // Left Right
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

//inOrder traversal
void inOrder(Node* root) {
    if (!root) return;
    printf("%d ", root->key);
    inOrder(root->left);
    inOrder(root->right);
}



int main() {
    int arr[] = {10, 3, 7, 1, 9, 20, 15};
    int n = sizeof(arr) / sizeof(arr[0]);


    buildMaxHeap(arr, n);
    printf("Max Heap (extracción):\n");
    
    Node* avl = NULL;
    int size = n;

    while (size > 0) {
        int maxVal = extractMax(arr, &size);
        printf("%d ", maxVal);
        avl = insertAVL(avl, maxVal);
    }

    printf("\n\nAVL inOrder traversal:\n");
    inOrder(avl);
    printf("\n");

    return 0;
}