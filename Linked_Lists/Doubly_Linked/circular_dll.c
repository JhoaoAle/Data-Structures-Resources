#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

Node* create_node(int value){
    Node* new_Node = (Node *)malloc(sizeof(Node));
    new_Node->data = value;
    new_Node->next = NULL;
    new_Node->prev = NULL;
    return new_Node;
}

typedef struct CircularDoublyLinkedList {
    Node* tail;
} CircularDoublyLinkedList;

CircularDoublyLinkedList* create_list(){
    CircularDoublyLinkedList* list = (CircularDoublyLinkedList*)malloc(sizeof(CircularDoublyLinkedList));
    list->tail = NULL;
    return list;
}

void free_list(CircularDoublyLinkedList* list){
    if (list == NULL || list->tail == NULL) return;

    Node* head = list->tail->next;
    Node* current = head;
    Node* temp;

    do {
        temp = current;
        current = current->next;
        free(temp);
    } while (current != head);

    free(list);
}

void insert_at_head(CircularDoublyLinkedList* list, int value){
    Node* new_node = create_node(value);

    if(list->tail == NULL){
        list->tail = new_node;
        new_node->next = new_node;
        new_node->prev = new_node;
    } else {
        Node* head = list->tail->next;

        new_node->next = head;
        new_node->prev = list->tail;

        head->prev = new_node;
        list->tail->next = new_node;
    }
}

void insert_at_tail(CircularDoublyLinkedList* list, int value){
    Node* new_node = create_node(value);

    if(list->tail == NULL){
        list->tail = new_node;
        new_node->next = new_node;
        new_node->prev = new_node;
    } else {
        Node* head = list->tail->next;

        new_node->next = head;
        new_node->prev = list->tail;

        list->tail->next = new_node;
        head->prev = new_node;

        list->tail = new_node;
    }
}

void insert_at_n(CircularDoublyLinkedList* list, int n, int value){
    if (n == 0){
        insert_at_head(list, value);
        return;
    }

    if (list->tail == NULL){
        printf("Out of bounds\n");
        return;
    }

    Node* new_node = create_node(value);
    Node* current = list->tail->next;
    int tracker = 0;

    while (tracker < n - 1){
        if (current == list->tail){
            printf("Out of bounds\n");
            free(new_node);
            return;
        }
        current = current->next;
        tracker++;
    }

    Node* next_node = current->next;

    new_node->next = next_node;
    new_node->prev = current;

    current->next = new_node;
    next_node->prev = new_node;

    if (current == list->tail)
        list->tail = new_node;
}

void print_circular_doubly_linked_list(CircularDoublyLinkedList* list){
    if (list->tail == NULL){
        printf("NULL\n");
        return;
    }

    Node* head = list->tail->next;
    Node* temp = head;

    do {
        printf("%d <-> ", temp->data);
        temp = temp->next;
    } while (temp != head);

    printf("Loop\n");
}

int main(){
    CircularDoublyLinkedList* my_list = create_list();

    insert_at_head(my_list, 1);
    insert_at_head(my_list, 2);
    insert_at_head(my_list, 3);

    insert_at_tail(my_list, 4);
    insert_at_tail(my_list, 5);

    print_circular_doubly_linked_list(my_list);

    insert_at_n(my_list, 5, 3);
    insert_at_n(my_list, 6, 4);

    print_circular_doubly_linked_list(my_list);

    free_list(my_list);
    return 0;
}