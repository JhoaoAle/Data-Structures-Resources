// C Program to Implement Doubly Linked List
#include <stdio.h>
#include <stdlib.h>

// defining a node
typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct DoublyLinkedList {
    struct Node* head;
    struct Node* tail;
} DLL;

// Function to create a new node with given value as data
Node* createNode(int data)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

DLL* createList(){
    DLL* list = (DLL*)malloc(sizeof(DLL));
    list->head = list->tail = NULL;
    return list;
}

// Function to insert a node at the beginning
void insertAtBeginning(DLL* list, int data)
{
    // creating new node
    Node* newNode = createNode(data);

    // check if DLL is empty
    if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
        return;
    }
    newNode->next = list->head;
    list->head->prev = newNode;
    list->head = newNode;
}

// Function to insert a node at the end
void insertAtEnd(DLL* list, int data)
{
    // creating new node
    Node* newNode = createNode(data);

    // check if DLL is empty
    if (list->head == NULL) {
        list->head = list->tail = newNode;
        return;
    }

    list->tail->next = newNode;
    newNode->prev = list->tail;
    list->tail = newNode;
}

// Function to insert a node at a specified position
/*void insertAtPosition(Node** head, int data, int position)
{
    if (position < 1) {
        printf("Position should be >= 1.\n");
        return;
    }

    // if we are inserting at head
    if (position == 1) {
        insertAtBeginning(head, data);
        return;
    }
    Node* newNode = createNode(data);
    Node* temp = *head;
    for (int i = 1; temp != NULL && i < position - 1; i++) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf(
            "Position greater than the number of nodes.\n");
        return;
    }
    newNode->next = temp->next;
    newNode->prev = temp;
    if (temp->next != NULL) {
        temp->next->prev = newNode;
    }
    temp->next = newNode;
}
*/
// Function to delete a node from the beginning
void deleteAtBeginning(DLL* list)
{
    // checking if the DLL is empty
    if (list->head == NULL) {
        printf("The list is already empty.\n");
        return;
    }
    Node* temp = list->head;
    list->head = list->head->next;
    if (list->head != NULL) {
        (list->head)->prev = NULL;
    }
    if (list->head->next == NULL) list->tail = list->head; 
    free(temp);
}
/*
// Function to delete a no if (list->head != NULL)de from the end
void deleteAtEnd(Node** head)
{
    // checking if DLL is empty
    if (*head == NULL) {
        printf("The list is already empty.\n");
        return;
    }

    Node* temp = *head;
    if (temp->next == NULL) {
        *head = NULL;
        free(temp);
        return;
    }
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->prev->next = NULL;
    free(temp);
}
*/
/*
// Function to delete a node from a specified position
void deleteAtPosition(Node** head, int position)
{
    if (*head == NULL) {
        printf("The list is already empty.\n");
        return;
    }
    Node* temp = *head;
    if (position == 1) {
        deleteAtBeginning(head);
        return;
    }
    for (int i = 1; temp != NULL && i < position; i++) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Position is greater than the number of "
               "nodes.\n");
        return;
    }
    if (temp->next != NULL) {
        temp->next->prev = temp->prev;
    }
    if (temp->prev != NULL) {
        temp->prev->next = temp->next;
    }
    free(temp);
}
*/
// Function to print the list in forward direction
void printListForward(DLL* list)
{
    Node* temp = list->head;
    printf("Forward List: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Function to print the list in reverse direction
void printListReverse(DLL* list)
{
    Node* temp = list->tail;
    printf("Reverse List: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->prev;
    }
    printf("\n");
}

int main()
{
    Node* head = NULL;
    DLL* my_list = createList();
    insertAtBeginning(my_list, 5);
    insertAtBeginning(my_list, 10);
    insertAtEnd(my_list, 20);

    printf("After Insertions:\n");
    printListForward(my_list);
    printListReverse(my_list);

    deleteAtBeginning(my_list);
    printf("After Insertions:\n");
    printListForward(my_list);
    printListReverse(my_list);
/*
    // Demonstrating various operations
    insertAtEnd(&head, 10);
    insertAtEnd(&head, 20);
    insertAtBeginning(&head, 5);
    insertAtPosition(&head, 15, 2); // List: 5 15 10 20

    printf("After Insertions:\n");
    printListForward(head);
    printListReverse(head);

    deleteAtBeginning(&head); // List: 15 10 20
    deleteAtEnd(&head); // List: 15 10
    deleteAtPosition(&head, 2); // List: 15

    printf("After Deletions:\n");
    printListForward(head);
*/
    return 0;
}