#include <stdio.h>
#include <stdlib.h>

// ====== DOUBLY LINKED LIST ====== 
// Each node has data, a pointer to the next node, and a pointer to the previous node

// Node structure for DLL
typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

// Global head and tail pointers
Node* head = NULL; 
Node* tail = NULL; 

// ====== DLL Operations ====== 

// 1. Insert at beginning
void insertBeginning(int value) {
    Node* newNode = (Node *)malloc(sizeof(Node));
    if (!newNode) { printf("Memory allocation failed!\n"); return; }
    newNode->data = value;
    newNode->prev = NULL;
    newNode->next = head;

    if (head == NULL) {           // empty list
        head = tail = newNode;
    } else {
        head->prev = newNode;
        head = newNode;
    }
}

// 2. Insert at end
void insertEnd(int value) {
    Node* newNode = (Node *)malloc(sizeof(Node));
    if (!newNode) { printf("Memory allocation failed!\n"); return; }
    newNode->data = value;
    newNode->next = NULL;
    newNode->prev = tail;

    if (head == NULL) {           // empty list
        head = tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
}

// 3. Insert at position (0-based index)
void insertAt(int pos, int value) {
    if (pos == 0) { insertBeginning(value); return; }

    Node* curr = head;
    for (int i = 0; curr != NULL && i < pos - 1; i++) {
        curr = curr->next;
    }
    if (curr == NULL) {           // position out of bounds
        printf("Position out of range!\n");
        return;
    }

    if (curr->next == NULL) {     // insert at end
        insertEnd(value);
        return;
    }

    Node* newNode = (Node *)malloc(sizeof(Node));
    if (!newNode) { printf("Memory allocation failed!\n"); return; }
    newNode->data = value;

    newNode->next = curr->next;
    newNode->prev = curr;
    curr->next->prev = newNode;
    curr->next = newNode;
}

// 4. Delete from beginning
void deleteBeginning() {
    if (head == NULL) { 
        printf("List is empty!\n"); 
        return; 
    }
    Node* temp = head;
    head = head->next;
    if (head != NULL) head->prev = NULL;
    else tail = NULL; // list became empty
    free(temp);
}

// 5. Delete from end
void deleteEnd() {
    if (tail == NULL) { 
        printf("List is empty!\n"); 
        return; 
    }
    Node* temp = tail;
    tail = tail->prev;
    if (tail != NULL) tail->next = NULL;
    else head = NULL; // list became empty
    free(temp);
}

// 6. Delete at position (0-based index)
void deleteAt(int pos) {
    if (head == NULL) { 
        printf("List is empty!\n"); 
        return; 
    }
    if (pos == 0) { deleteBeginning(); return; }

    Node* curr = head;
    for (int i = 0; curr != NULL && i < pos; i++) {
        curr = curr->next;
    }
    if (curr == NULL) {
        printf("Position out of range!\n");
        return;
    }

    if (curr->next != NULL) curr->next->prev = curr->prev;
    else tail = curr->prev; // deleting last node

    if (curr->prev != NULL) curr->prev->next = curr->next;
    else head = curr->next; // deleting first node

    free(curr);
}

// 7. Display forward (head -> tail)
void displayForward() {
    Node* curr = head;
    printf("Forward: ");
    while (curr != NULL) {
        printf("%d <-> ", curr->data);
        curr = curr->next;
    }
    printf("NULL\n");
}

// 8. Display reverse (tail -> head)
void displayReverse() {
    Node* curr = tail;
    printf("Reverse: ");
    while (curr != NULL) {
        printf("%d <-> ", curr->data);
        curr = curr->prev;
    }
    printf("NULL\n");
}

// ---------------- Swap Helpers ---------------- //

// Utility: swap two *nodes* in DLL by adjusting pointers
void swapNodes(Node* a, Node* b) {
    if (!a || !b || a == b) return;

    // If nodes are adjacent (a before b)
    if (a->next == b) {
        Node* ap = a->prev;
        Node* bn = b->next;

        if (ap) ap->next = b; else head = b;
        if (bn) bn->prev = a; else tail = a;

        b->prev = ap;
        b->next = a;
        a->prev = b;
        a->next = bn;
        return;
    }

    // If nodes are adjacent (b before a), reuse the same logic
    if (b->next == a) {
        swapNodes(b, a);
        return;
    }

    // Non-adjacent nodes
    Node* ap = a->prev; Node* an = a->next;
    Node* bp = b->prev; Node* bn = b->next;

    // Relink neighbors to opposite nodes
    if (ap) ap->next = b; else head = b;
    if (an) an->prev = b; else tail = b;

    if (bp) bp->next = a; else head = a;
    if (bn) bn->prev = a; else tail = a;

    // Swap a and b internals
    a->prev = bp; a->next = bn;
    b->prev = ap; b->next = an;
}

// Swap two nodes by their values (first occurrences)
void swapByValue(int x, int y) {
    if (x == y) return;
    Node* a = head;
    Node* b = head;

    while (a && a->data != x) a = a->next;
    while (b && b->data != y) b = b->next;

    if (!a || !b) {
        printf("Value not found for swap!\n");
        return;
    }
    swapNodes(a, b);
}

// Swap two nodes by their positions (0-based)
void swapByPosition(int pos1, int pos2) {
    if (pos1 == pos2) return;

    // Ensure pos1 < pos2 for simpler traversal
    if (pos2 < pos1) { int t = pos1; pos1 = pos2; pos2 = t; }

    Node* a = head; 
    Node* b = head;
    int i = 0;

    while (a && i < pos1) { a = a->next; i++; }
    i = 0;
    while (b && i < pos2) { b = b->next; i++; }

    if (!a || !b) {
        printf("Position out of range for swap!\n");
        return;
    }
    swapNodes(a, b);
}

// ====== MAIN ====== 
int main() {
    // Build list
    insertEnd(10); insertEnd(20); insertEnd(30); insertEnd(40); insertEnd(50);
    displayForward();    // Forward: 10 <-> 20 <-> 30 <-> 40 <-> 50 <-> NULL
    displayReverse();    // Reverse: 50 <-> 40 <-> 30 <-> 20 <-> 10 <-> NULL

    // Swap by value
    swapByValue(20, 50);
    displayForward();    // Forward: 10 <-> 50 <-> 30 <-> 40 <-> 20 <-> NULL

    // Swap by position
    swapByPosition(1, 3);
    displayForward();    // Forward: 10 <-> 40 <-> 30 <-> 50 <-> 20 <-> NULL

    // Insert/delete demos to show consistency
    insertBeginning(5);         // 5 at front
    insertAt(3, 15);            // insert 15 at index 3
    displayForward();

    deleteBeginning();          // remove front
    deleteEnd();                // remove tail
    deleteAt(2);                // remove element at index 2
    displayForward();

    return 0;
}

